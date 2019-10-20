# Developing C++
## Selecting a configuration
```Ctrl-Shift-P``` then C/C++: Select a Configuration...
## Windows
### Prerequisites
* Visual Studio Code
* C++ extension for VS Code
* Visual Studio Build Tools (installed by Node Js)
### Starting VS Code
* Start VS Code in developer command prompt:
Type ```developer``` in Windows Start Menu and select ```Developer Command Prompt for VS 2017```
* From there, run ```code```
### Configuring VS Code
* type ```Ctrl Shift P```, then type ```C/C++```
* Select ```C/C++ Edit Configuration (UI)```. This creates ```c_cpp_properties.json```
###  Create build task
* type ```Ctrl Shift P```, then type ```task``` and select ```Configure default build task```. Choose ```others```. This create ```tasks.json```.
* replace content with:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "msvc build",
            "type": "shell",
            "command": "cl.exe",
            "args": [
                "/Zi", // Symbols
                "/Fe:", // executable name                
                "helloworld.exe",
                "helloworld.cpp"
            ],
            "group":  {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "reveal":"always"
            },
            "problemMatcher": "$msCompile"
        }
    ]
}

```

### Create Debug task
* From the main menu, choose ```Debug > Add Configuration...``` and then choose ```C/C++ Windows (Launch)```. 

## Linux
### Prerequisites
