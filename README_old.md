# CNCS Ecosystem

## Overview

This repository contains the CNCS (Computer Numerical Control System) ecosystem, a modular C++ project for CNC machine control, simulation, and related tooling. The project is organized into multiple components, including core CNC logic, GUI, database control, web services, and more. It also integrates several third-party libraries as git submodules.

---

## Repository Structure

```
.gitignore
.gitmodules
CHANGELOG.md
CODE_OF_CONDUCT.md
CONTRIBUTING.md
LICENSE
NOTICE.md
README.md
SECURITY.md
.github/
docs/
ignored/
sourcecode/
version-generator/
```

### Top-Level Files

- **.gitignore**: Specifies files and directories to be ignored by git.
- **.gitmodules**: Lists git submodules (third-party dependencies).
- **CHANGELOG.md**: Project changelog.
- **CODE_OF_CONDUCT.md**: Code of conduct for contributors.
- **CONTRIBUTING.md**: Contribution guidelines.
- **LICENSE**: Project license.
- **NOTICE.md**: Notices and attributions.
- **README.md**: This file.
- **SECURITY.md**: Security policy.

### Key Directories

#### [.github/](.github/)
- Contains GitHub-specific files, such as issue and pull request templates.

#### [docs/](docs/)
- **changelog/**: Additional changelog files.
- **errors/**: Documentation of error codes and messages.
- Project documentation and guides.

#### [ignored/](ignored/)
- Contains files not included in the main build, such as:
  - `Befehle G-code D5.pdf`, `Befehle M-code D5.pdf`: G-code and M-code command references.
  - `server.cpp`, `server_windows.cpp`: Example or legacy server code.

#### [sourcecode/](sourcecode/)
- **CNCS.sln**: Visual Studio solution file for the entire project.
- **.binaries/**, **.binaries-int/**, **.vs/**: Build artifacts and IDE metadata (should be ignored by git).
- **CMD/**: Command processing and handling.
- **DATABASE-CTRL/**: Database control and management.
- **GUI/**: Graphical user interface components.
- **include/**: Third-party libraries as git submodules:
  - **gitmodules/imgui/**: [Dear ImGui](sourcecode/include/gitmodules/imgui/README.md) (immediate-mode GUI).
  - **gitmodules/pugixml/**: [pugixml](sourcecode/include/gitmodules/pugixml/README.md) (XML processing).
  - **gitmodules/tracy/**: [Tracy Profiler](sourcecode/include/gitmodules/tracy/README.md) (profiling).
- **INTERPRETER/**: G-code/M-code interpreter and CNC logic.
- **MATH/**: Mathematical utilities and algorithms.
- **TESTS/**: Unit and integration tests.
- **USB/**: USB communication and device handling.
- **WEBCLIENT/**: Web client components.
- **WEBSERVER/**: Web server implementation.
- **WEBSERVICES/**: Web service APIs and logic.

#### [version-generator/](version-generator/)
- Scripts and tools for version management.

---

## Building the Project

1. **Clone the repository with submodules:**
   ```sh
   git clone --recurse-submodules <repo-url>
   ```

2. **Open the solution:**
   - Open `sourcecode/CNCS.sln` in Visual Studio.

3. **Build:**
   - Build the solution using Visual Studio's build system.

---

## Third-Party Libraries

- [Dear ImGui](sourcecode/include/gitmodules/imgui/README.md): Immediate-mode GUI library for C++.
- [pugixml](sourcecode/include/gitmodules/pugixml/README.md): Fast XML parser for C++.
- [Tracy Profiler](sourcecode/include/gitmodules/tracy/README.md): Real-time, nanosecond resolution profiler.

Each library includes its own documentation in its respective directory.

---

## Documentation

- See the [docs/](docs/) directory for error documentation, changelogs, and additional guides.
- Each submodule in `sourcecode/include/gitmodules/` contains its own README and documentation.

---

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests.

---

## License

This project is licensed under the terms described in [LICENSE](LICENSE).

---

## Security

For security issues, see [SECURITY.md](SECURITY.md).

---

## Contact

For questions or support, please open an issue or pull request via GitHub.
