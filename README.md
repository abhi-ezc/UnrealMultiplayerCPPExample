# TestMultiplayerProject - Unreal Engine 5.2 (Store Edition)

This project is a basic test project showcasing C++, Blueprints, and Multiplayer functionality in Unreal Engine 5.2 (Store Edition). Developed by Abhinav MK.

### Features:

- Spawn an Actor to the screen
- Move the Actor along Z and X axis
- Rotate the Actor around the X axis
- Scale the Actor in XYZ (Note: Scaling in Multiplayer is not supported due to non-replicated transform property)
- Undo the previous move
- Reset the Actor to its initial position
- Delete the spawned Actor

### Requirements:

- Unreal Engine 5.2 (Store Edition)

### Building the Project:

1.Switch Unreal Engine Version:

- Right-click on the .uproject file and select "Switch Unreal Engine Version."
- Choose Unreal Engine 5.2 from the version selector.

2.Generate Visual Studio Project Files:

- Right-click on the .uproject file and select "Generate Visual Studio project files."
- This will create a solution file.

3.Open and Build in Visual Studio:

- Open the generated solution file in Visual Studio.
- Build the project using the "Development Editor Win64" configuration.

4.Running the Project:

- You can launch the project in two ways:
  - Double-click the .uproject file.
  - In Visual Studio, click the "Play" button.

### Note:

Due to limitations of the Unreal Engine 5.2 Store Edition, building dedicated Server and Client targets is not possible. This project is intended to be run as a single-player instance.
