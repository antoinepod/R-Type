EPITECH R-Type Server Protocol

The commands from client to server that are implemented:

    NONE = 0
    UP = 2
    DOWN = 4
    LEFT = 8
    RIGHT = 16
    SHOOT_SIMPLE = 32
    SHOOT_LASER = 64
    SHOOT_ROCKET = 128
    LEVEL1 = 256
    LEVEL2 = 512
    LEVEL3 = 1024
    DISCONNECT = 2048
    
Those commands are serialized and sent as bytes to the server.
(thanks to Network/Serialization cpp and hpp files)

Server-Replies

The server replies with an serialized std::vector<IObject> (see Network/Objects folder)
(thanks to Network/Serialization cpp and hpp files)
It contains all the data present in the game, with their positions, their infos and all what is needed to display properly.


Client-Reception
The client receive all the datas serialized, and deserialise with Network/Serialization cpp and hpp files.
