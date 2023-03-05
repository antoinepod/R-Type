# 👾 R-Type

## 📝 Description
R-Type is a game where you have to destroy all the enemies that are coming to you. You can shoot with your spaceship, and you can also use special weapons. You can play with friends in a multiplayer mode.

## 📖 Documentation
You can see our documentation in the documentation folder. Use vscode to open a better view, on a live server.

<br/>

## ⚙️ Installation
First, you need to clone the repo, and its git submodules:
```sh
git clone https://github.com/EpitechPromo2025/B-CPP-500-LIL-5-2-rtype-william.mallevays.git --recurse-submodules
```

<br/>

### - Windows : 
1. Run Visual Studio as administrator
2. Then you'll have to right click on "CMakeList.txt" located in the solution explorer
3. Click on "Configure cache"
4. Now click on "x64-Debug" at the top of your screen, and select "Manage configurations..."
5. Then click on the "+" sign, and select "x64-Release" and save (ctrl + s)
6. Once it is done you just have to click on "Select startup item" on the top of the screen
7. And select "r-type_client.exe" or "r-type_server.exe" to compile and launch the client or the server

<br/>


### - Linux :
```sh
mkdir build && cd build
```
```sh
cmake ..
```
```sh
make
```

Launch the R-Type client:
```sh
./r-type_client
```

Launch the R-Type server:
```sh
./r-type_server
```

<br/>


## 💻 How to play

### ⌨️ Keys
- `Arrows`: Up, Down, Left, Right
- `Space`: Simple shoot
- `X`: Laser shoot
- `C`: Rocket shoot 
### 🎮 Controller (DualShock 4 taken as an example)
- `Left joystick`: Up, Down, Left, Right
- `Cross`: Simple shoot
- `Circle`: Laser shoot
- `Triangle`: Rocket shoot 