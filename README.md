# Advanced Locomotion System Refactored

![Image](https://github.com/Sixze/ALS-Refactored/raw/main/Screenshots/Header.gif)

Completely refactored and bug fixed version of the [Community Version](https://github.com/dyanikoglu/ALS-Community) of [Advanced Locomotion System V4](https://www.unrealengine.com/marketplace/en-US/product/advanced-locomotion-system-v1) for **Unreal Engine 4.26**.

## Supported Platforms

- Windows

*macOS, iOS, Linux, Android, and console builds are not tested. Use the plugin on those platforms with your own risk.*

## Features

- Based on latest marketplace release.
- Fully implemented in C++.
- Plugin structure.
- Highly optimized for production.
- Full replication support with low bandwidth usage.
- Lots of bug fixes additional to marketplace version.

## Known Issues & Discussion

- See [Issues](https://github.com/Sixze/ALS-Refactored/issues) section for list of known issues.
- See [Discussions](https://github.com/Sixze/ALS-Refactored/discussions) section to discuss anything about the plugin, and ask questions. Please do not open an issue to ask questions about the plugin.

## Setting Up the Plugin

- **C++ project is a requirement. Blueprint projects are currently not supported.**
- Clone the repository inside your project's plugins folder, or download the latest release and extract it into your project's plugins folder.
- Put `Config/DefaultInput.ini` from the plugin folder inside your project's config folder. If your project already have this file, then merge it into yours.
- Regenerate Visual Studio project files and build your project.
- Launch the project, and enable plugin content viewer as seen below. This will show contents of the plugin in your content browser:
![image](https://github.com/Sixze/ALS-Refactored/raw/main/Screenshots/ShowPluginContent.png)

## License & Contribution

**Source code** of the plugin is licensed under MIT license, and other developers are encouraged to fork the repository, open issues & pull requests to help the development.