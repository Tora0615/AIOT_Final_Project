# NCHU AIOT Class' final project  

## Main Idea

Water source's clean level will affect our health,so we need a system to detcet water. When detected toxic heavy metal, the system will close water supply immediately. This is the simulate system of it.

## Structure

Sensors detect water is toxic or not then transmite to server.
Server use AI model to judge the level of danger and then contorl the relay to open/close pump.

Unfortunately, we don't have these sensors, so use website send data to simulate.

```code
          server (Run AI model to determine whether the water is toxic or not)
            |   |
  (control) |   |----Web (get user's input simulate test data)
            |
            |----Arduino
                    |          (control)
                    |------ relay ---  pump  
                    |          
                    |------ (toxic sensors) 
                        
```

## Demo Link (Include full presentation)

<https://youtu.be/qgEsq-HO2BE?t=636>

## Division of labor and special thanks ❤️

[@luder624](https://github.com/luder624) -- Speaker

[@FeHeap](https://github.com/FeHeap) -- Backend Developer

[@jhaorong](https://github.com/jhaorong) -- AI trainer

me -- IOT system designer
