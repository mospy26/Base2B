Design pattern used: Factory method
	Factory method is used to delegate instantiation of individual entities (cloud, cactus, bird) to the subclasses.
	This way, we can choose to create instances of them without specifying the specifics of the object from our dialog game class.

OO Design
	Encapsulation:
		Methods and variables intrinsic to a specific object are scoped to instances of the class itself through access specifiers.
		e.g. 	UpdateSprite method is intrinsic to Entity objects and so has a protected access specifier
	Abstraction:
		Low end methods such as the update sprite method are encapsulated within their own objects. 
		To access these in higher up code, the encapsulating methods are called.
		e.g. 	An Entity object updates its sprite when it calls its render function.
			This itself is encapsulated within a renderBackground method which the game dialog calls.
	Polymorphism:
		Unused currently but different entities will have different behaviours in collision
	Inheritance:
		All entities which traverse across the screen as background share similar properties and therefore inherit from a parent entity class.
		e.g. Properties such as velocity and methods like updateSprite are inherited from the Entity class into Cloud class.

Coding Style
	Open curly brackets on the same line
	Use namespace std if requiring string
	Use this-> notation to access member variables
	4 space indents
	config.txt and resources located inside build folder

Extensions
	Night/Day cycle for background
	Moon for night cycle travelling on an arc path with moon phases
	Background generated randomly
	Parallax effect with background clouds
 	Score displayed as sprite
	Animated stickman + background
	
