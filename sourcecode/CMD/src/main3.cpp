#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Flag {
public:
    std::string name, short_name, description;
    bool requires_value = false;
    std::string value;
    bool is_set = false;

    Flag() = default;
    Flag(std::string name, std::string short_name, bool requires_value,
         std::string description)
        : name(std::move(name)), short_name(std::move(short_name)),
          requires_value(requires_value), description(std::move(description)) {}
};

class ParsingNode {
protected:
    std::string node_name;
    std::string description;

    std::map<std::string, std::shared_ptr<ParsingNode>> subcommands;
    std::map<std::string, Flag> flags;

public:
    ParsingNode(std::string name, std::string desc = "")
        : node_name(std::move(name)), description(std::move(desc)) {
        // Add help flag by default
        add_flag("help", "h", false, "Show this help message");
    }

    virtual ~ParsingNode() = default;

    void add_flag(const std::string& name, const std::string& short_name,
                  bool requires_value, const std::string& desc) {
        flags[name] = Flag(name, short_name, requires_value, desc);
    }

    void add_subcommand(const std::shared_ptr<ParsingNode>& cmd) {
        subcommands[cmd->node_name] = cmd;
    }

    virtual void print_help() const {
        std::cout << "Usage: " << node_name << " [options]";

        if (!subcommands.empty()) {
            std::cout << " <subcommand>\n\nSubcommands:\n";
            for (const auto& [name, cmd] : subcommands) {
                std::cout << "  " << std::setw(10) << name << " - "
                          << cmd->description << "\n";
            }
        } else {
            std::cout << "\n";
        }

        if (!flags.empty()) {
            std::cout << "\nOptions:\n";
            for (const auto& [name, flag] : flags) {
                std::cout << "  ";
                if (!flag.short_name.empty())
                    std::cout << "-" << flag.short_name << ", ";
                else
                    std::cout << "    ";
                std::cout << "--" << std::setw(10) << std::left << flag.name;
                std::cout << " " << flag.description << "\n";
            }
        }
    }

    bool parse(int argc, char* argv[], int start_index = 1) {
        std::vector<std::string> args(argv + start_index, argv + argc);

        for (size_t i = 0; i < args.size();) {
            const std::string& arg = args[i];

            if (arg.rfind("--", 0) == 0) {
                std::string name = arg.substr(2);
                if (name == "help") {
                    print_help();
                    return false;
                }
                if (flags.count(name)) {
                    Flag& flag = flags[name];
                    flag.is_set = true;
                    if (flag.requires_value) {
                        if (i + 1 >= args.size()) {
                            std::cerr << "Flag --" << name
                                      << " requires a value.\n";
                            return false;
                        }
                        flag.value = args[i + 1];
                        i += 2;
                    } else {
                        i++;
                    }
                } else {
                    std::cerr << "Unknown flag: " << arg << "\n";
                    return false;
                }
            } else if (arg.rfind("-", 0) == 0) {
                std::string short_name = arg.substr(1);
                if (short_name == "h") {
                    print_help();
                    return false;
                }
                bool found = false;
                for (auto& [_, flag] : flags) {
                    if (flag.short_name == short_name) {
                        flag.is_set = true;
                        if (flag.requires_value) {
                            if (i + 1 >= args.size()) {
                                std::cerr << "Flag -" << short_name
                                          << " requires a value.\n";
                                return false;
                            }
                            flag.value = args[i + 1];
                            i += 2;
                        } else {
                            i++;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cerr << "Unknown short flag: " << arg << "\n";
                    return false;
                }
            } else if (subcommands.count(arg)) {
                return subcommands[arg]->parse(
                    argc, argv, static_cast<int>(i + start_index + 1));
            } else {
                return run(arg, std::vector<std::string>(args.begin() + i,
                                                         args.end()));
            }
        }

        return run("", {});
    }

    virtual bool run(const std::string& subcmd,
                     const std::vector<std::string>& args) {
        print_help(); // default fallback
        return false;
    }
};

// Example: build command
class BuildCommand : public ParsingNode {
public:
    BuildCommand() : ParsingNode("build", "Compile the source code") {
        add_flag("jobs", "j", true, "Number of parallel jobs");
        add_flag("verbose", "v", false, "Enable verbose output");
    }

    bool run(const std::string&,
             const std::vector<std::string>& args) override {
        std::cout << "[BuildCommand] Running build...\n";
        if (flags["verbose"].is_set)
            std::cout << "Verbose mode is enabled.\n";
        if (flags["jobs"].is_set)
            std::cout << "Jobs: " << flags["jobs"].value << "\n";
        return true;
    }
};

// Example: run command
class RunCommand : public ParsingNode {
public:
    RunCommand() : ParsingNode("run", "Execute the program") {}

    bool run(const std::string&,
             const std::vector<std::string>& args) override {
        std::cout << "[RunCommand] Executing with args:\n";
        for (const auto& a : args) {
            std::cout << " - " << a << "\n";
        }
        return true;
    }
};

// Root command
class RootCommand : public ParsingNode {
public:
    RootCommand() : ParsingNode("myapp", "A sample CLI app") {
        add_subcommand(std::make_shared<BuildCommand>());
        add_subcommand(std::make_shared<RunCommand>());
    }

    bool run(const std::string&, const std::vector<std::string>&) override {
        std::cout << "You must specify a subcommand.\n\n";
        print_help();
        return false;
    }
};

int main(int argc, char* argv[]) {
    RootCommand root;
    root.parse(argc, argv);
    return 0;
}
