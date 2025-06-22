#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Flag {
public:
    std::string name;
    std::string short_name;
    bool has_value;
    std::string value;
    bool is_set = false;

    Flag() = default;

    Flag(const std::string& name, const std::string& short_name = "",
         bool has_value = false)
        : name(name), short_name(short_name), has_value(has_value) {}
};

class Command {
protected:
    std::map<std::string, Flag> flags;
    std::vector<std::string> positional_args;

public:
    std::string name;

    Command(const std::string& name) : name(name) {}

    void add_flag(const std::string& long_name,
                  const std::string& short_name = "", bool has_value = false) {
        flags[long_name] = Flag(long_name, short_name, has_value);
    }

    bool parse_flags(std::vector<std::string>& args) {
        for (size_t i = 0; i < args.size();) {
            std::string arg = args[i];

            if (arg.rfind("--", 0) == 0) {
                std::string key = arg.substr(2);
                auto it = flags.find(key);
                if (it == flags.end())
                    return false;
                it->second.is_set = true;

                if (it->second.has_value) {
                    if (i + 1 >= args.size())
                        return false;
                    it->second.value = args[i + 1];
                    i += 2;
                } else {
                    i++;
                }
            } else if (arg.rfind("-", 0) == 0) {
                std::string key = arg.substr(1);
                auto found = std::find_if(
                    flags.begin(), flags.end(),
                    [&](const auto& p) { return p.second.short_name == key; });
                if (found == flags.end())
                    return false;

                found->second.is_set = true;
                if (found->second.has_value) {
                    if (i + 1 >= args.size())
                        return false;
                    found->second.value = args[i + 1];
                    i += 2;
                } else {
                    i++;
                }
            } else {
                positional_args.push_back(arg);
                i++;
            }
        }
        return true;
    }

    Flag get_flag(const std::string& name) const { return flags.at(name); }

    std::vector<std::string> get_positionals() const { return positional_args; }

    virtual void execute() = 0; // each command defines its own behavior
};

class BuildCommand : public Command {
public:
    BuildCommand() : Command("build") {
        add_flag("verbose", "v");
        add_flag("jobs", "j", true);
    }

    void execute() override {
        std::cout << "[BuildCommand] Executing build...\n";
        if (flags["verbose"].is_set)
            std::cout << "Verbose mode ON\n";
        if (flags["jobs"].is_set)
            std::cout << "Jobs: " << flags["jobs"].value << "\n";
    }
};

class RunCommand : public Command {
public:
    RunCommand() : Command("run") {}

    void execute() override {
        std::cout << "[RunCommand] Running with input:\n";
        for (const auto& arg : get_positionals()) {
            std::cout << " - " << arg << "\n";
        }
    }
};

class CLIParser {
    std::map<std::string, Command*> commands;

public:
    void add_command(Command* cmd) { commands[cmd->name] = cmd; }

    void parse(int argc, char* argv[]) {
        if (argc < 2) {
            std::cerr << "No command provided\n";
            return;
        }

        std::string cmd_name = argv[1];
        if (commands.find(cmd_name) == commands.end()) {
            std::cerr << "Unknown command: " << cmd_name << "\n";
            return;
        }

        Command* cmd = commands[cmd_name];
        std::vector<std::string> args(argv + 2, argv + argc);

        if (!cmd->parse_flags(args)) {
            std::cerr << "Error parsing flags\n";
            return;
        }

        cmd->execute();
    }
};

int main(int argc, char* argv[]) {
    CLIParser parser;
    parser.add_command(new BuildCommand());
    parser.add_command(new RunCommand());
    parser.parse(argc, argv);
    return 0;
}
