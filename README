======= CONFIG FILE INSTRUCTIONS FOR STAGE 2 =======
To enable stage 2, the setting "stage: 2" should be in the config file. Otherwise, stage 1 will run.
To enable the testing interface, the settings "stage: 2" and "testMode: on" should be in the config file.
To add obstacles to the stage 2 obstacle layout, the setting in the config file should look like this (without quotes):

"obstacles: OBSTACLE|OBSTACLE|OBSTACLE|..." -- each obstacle is separated by a |

The format for an OBSTACLE looks like this (without quotes):
"WIDTH,HEIGHT,Y_POSITION,SPACING_UNTIL_NEXT_OBSTACLE,COLOUR_RED,COLOUR_BLUE,COLOUR_GREEN,FLY_RATE"

======= Structural Design Pattern Used =======
Decorator Pattern
- ColouredEntity: Decorates the Entity class's render method by recolouring the sprite before calling the original render method
- FlyingEntity: Decorates the Entity class's update method by adding flying and vertical collision logic before calling the original update method.
- SwapRendererStage: Decorates a GameStage by modfiying the Renderer that will be passed to it, therefore changing the way the game is rendered.

======= Coding Style =======
See README_STAGE1

======= Extensions =======
== Extendible Testing Interface ==
While the testing interface was part of the assignment, this is a more advanced/extendible version which allows test cases to subclass from the TestRunner interface which are run as independent game worlds for testing game features in isolation. TestRunners are queried for their status by the TestingDialog before going to the next TestRunner upon a PASS or FAIL. The game is visible to the user while the test case are running, and its status is shown in the top left corner of the screen. 

To enable the testing interface, the config file should have the "stage: 2" and "testMode: on" settings. The program will exit upon finishing all test cases.

== Game Stages ==
Game stages (stage 1, 2 and the testing interface) share a common GameStage subclass, and the Game class is the main QWidget which redirects all events to the active GameStage, which can be easily changed via the setStage method. This means it's now very easy to switch between stages (or even different levels of the same stage, if implemented in a later stage) at runtime, whereas before it was unchangeable.

== Switchable Rendering Modes ==
With some refactoring of the original code, all render methods now take a Renderer rather than a QPainter (note that QPainter has no virtual methods so could not be extended). GameStage has a SwapRendererStage decorator which can switch out the Renderer for a different one, changing how the game world is drawn. For now, it's used in stage 2 (and its testing mode) to toggle a debugging version which displays collision boxes and positional text by pressing the "1" key.

== Double/Multiple Jumps ==
The stickman can jump a number of times while in the air before hitting the ground as specified in its constructor. By default, this is set to 2 meaning the stickman can jump once off the ground and then once more in the air before no further jumps are allowed until hitting the ground.

== Flying Obstacles ==
Obstacles can fly up or down as specified by the final value for each obstacle in the config file layout. When the stickman jumps on top of a obstacle the obstacle will stop flying until the stickman is no longer on top of it.