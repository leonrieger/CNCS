#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace cli {

    class flag {
    public:
        std::string name, short_name, description;
        bool required = false;
        bool takes_value = false;
        bool is_set = false;
        std::string value;

        flag() = default;

        flag(std::string name_, std::string short_name_, bool takes_value_,
             bool required_, std::string description_)
            : name(std::move(name_)), short_name(std::move(short_name_)),
              description(std::move(description_)), required(required_),
              takes_value(takes_value_) {}
    };

    class node : public std::enable_shared_from_this<node> {
        std::string node_name;
        std::string node_desc;
        std::map<std::string, std::shared_ptr<node>> children;
        std::map<std::string, flag> flags;
        std::weak_ptr<node> parent;

    public:
        explicit node(std::string name = "", std::string desc = "")
            : node_name(std::move(name)), node_desc(std::move(desc)) {
            append_flag("help", "h", false, false, "Show help message");
        }

        std::shared_ptr<node> append_child(const std::string& name,
                                           const std::string& desc = "") {
            auto child = std::make_shared<node>(name, desc);
            child->parent = shared_from_this();
            children[name] = child;
            return child;
        }

        node& append_flag(const std::string& name,
                          const std::string& short_name, bool takes_value,
                          bool required, const std::string& desc) {
            flags[name] = flag(name, short_name, takes_value, required, desc);
            return *this;
        }

        std::shared_ptr<node> child(const std::string& name) {
            if (children.count(name))
                return children[name];
            return nullptr;
        }

        bool parse(int argc, char* argv[], int index = 1) {
            std::vector<std::string> args(argv + index, argv + argc);

            for (size_t i = 0; i < args.size();) {
                const std::string& arg = args[i];
                if (arg.rfind("--", 0) == 0) {
                    std::string name = arg.substr(2);
                    if (name == "help") {
                        print_help();
                        return false;
                    }
                    if (flags.count(name)) {
                        flag& f = flags[name];
                        f.is_set = true;
                        if (f.takes_value) {
                            if (i + 1 >= args.size()) {
                                std::cerr << "Flag --" << name
                                          << " requires a value.\n";
                                return false;
                            }
                            f.value = args[i + 1];
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
                    bool found = false;
                    for (auto& [_, f] : flags) {
                        if (f.short_name == short_name) {
                            f.is_set = true;
                            if (f.takes_value) {
                                if (i + 1 >= args.size()) {
                                    std::cerr << "Flag -" << short_name
                                              << " requires a value.\n";
                                    return false;
                                }
                                f.value = args[i + 1];
                                i += 2;
                            } else {
                                i++;
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        std::cerr << "Unknown flag: -" << short_name << "\n";
                        return false;
                    }
                } else if (children.count(arg)) {
                    return children[arg]->parse(
                        argc, argv, static_cast<int>(i + index + 1));
                } else {
                    // Unknown subcommand or argument
                    std::cerr << "Unknown command or argument: " << arg << "\n";
                    return false;
                }
            }

            // Check required flags
            for (const auto& [name, f] : flags) {
                if (f.required && !f.is_set) {
                    std::cerr << "Missing required flag: --" << name << "\n";
                    return false;
                }
            }

            return run();
        }

        void print_help() const {
            std::cout << "Usage: " << full_path() << " [options]";
            if (!children.empty())
                std::cout << " <subcommand>";
            std::cout << "\n";

            if (!node_desc.empty())
                std::cout << "\n" << node_desc << "\n";

            if (!children.empty()) {
                std::cout << "\nSubcommands:\n";
                for (const auto& [name, child] : children) {
                    std::cout << "  " << std::setw(12) << name << " - "
                              << child->node_desc << "\n";
                }
            }

            if (!flags.empty()) {
                std::cout << "\nOptions:\n";
                for (const auto& [_, f] : flags) {
                    std::cout << "  ";
                    if (!f.short_name.empty())
                        std::cout << "-" << f.short_name << ", ";
                    else
                        std::cout << "    ";
                    std::cout << "--" << std::setw(10) << std::left << f.name;
                    std::cout << (f.required ? " (required)" : "") << "  "
                              << f.description << "\n";
                }
            }
        }

        std::string full_path() const {
            if (auto p = parent.lock()) {
                return p->full_path() + " " + node_name;
            } else {
                return node_name;
            }
        }

        // Override this per-command
        virtual bool run() {
            print_help();
            return true;
        }

        // To support shared_from_this in base class
        class enable_shared_from_this_virtual
            : public std::enable_shared_from_this<node> {
        protected:
            virtual ~enable_shared_from_this_virtual() = default;
        };

        friend std::shared_ptr<node> make_root(const std::string&,
                                               const std::string&);
    };

    std::shared_ptr<node> make_root(const std::string& name,
                                    const std::string& desc = "") {
        struct RootNode : public node {
            RootNode(const std::string& name, const std::string& desc)
                : node(name, desc) {}
        };
        return std::make_shared<RootNode>(name, desc);
    }

} // namespace cli


int main(int argc, char* argv[]) {
    using namespace cli;

    auto root = make_root("myapp", "A pugixml-style CLI parser");

    auto build = root->append_child("build", "Build the project");
    build->append_flag("jobs", "j", true, true, "Number of jobs");
    build->append_flag("verbose", "v", false, false, "Verbose output");

    auto run = root->append_child("run", "Run the program");
    run->append_flag("input", "i", true, true, "Input file");

    return root->parse(argc, argv) ? 0 : 1;
}
