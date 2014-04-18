Project-2
=========

# CS372 PostScript Shapes Project
## Authors:
	Igor K.
	Dustin D.
	Eric P.

## Description:
In this project, you will implement a C++ library that we will call CPS, short for "C++ to PostScript." CPS will allow its user to specify drawings at a high level of abstraction, and output the drawings as PostScript. CPS consists of:
* A **shape language** that allows basic shapes such as squares, circles, and polygons to be defined, rotated and scaled versions, and aggregate shapes, for example a vertical "stack".
* A **shapes-to-PostScript translator** that takes as input a drawing specified using CPS's shape language and produces a PostScript file from it.

## Specification
### Shape language
The CPS shape language relies on the following fundamental notions:

* **Bounding box.** Every shape has a bounding box: an imaginary rectangle that encloses the shape. Bounding boxes are not drawn. The height (width) of a shape is the height (width) of its bounding box. Bounding boxes are shown below using dotted lines.

* **Current point.** The current point represents the coordinates of the current location of the cursor. In PostScript, these coordinates are given by the command currentpoint. A shape is drawn so that its bounding box is centered around the current point. The center of an bounding box is shown below as a small black circle.

* **Units.** Postscript's basic unit of measurement is 1/72 of an inch. When referring to lengths below (e.g. radius, width or height), we are assuming this measurement system. For example, if a shape has a height of 36, that means 36 units, which is 36/72 = 1/2 inch.

CPS is based on a language of immutable shapes, that are either basic or compound.

**Basic shapes**
Basic shapes are primitive shapes that can be created without reference to any other shapes.

1. **Circle(double radius).** Creates a circle with the given radius. The height and width of a circle are both 2*radius.

2. **Polygon(double numSides, double sideLength).** Creates a regular polygon with the given number of sides, each of the given length, oriented so that its lowermost side is horizontal.

3. **Rectangle(double width, double height).** Creates a rectangle of the given width and height.

4. **Spacer(double width, double height).** Like a rectangle, but without drawn borders. A spacer is not visible on the page.

5. **Square(double sideLength).** Equivalent to Polygon(4, sideLength).

6. **Triangle(double sideLength).** Equivalent to Polygon(3, sideLength).

**Compound shapes**
Compound shapes are shapes that are constructed from one or more other shapes, which may themselves be basic or compound.

* **Rotated(Shape shape, RotationAngle rotationAngle).** Takes a shape and a rotation angle, which is either 90, 180 or 270 degrees. Creates a version of the shape that is rotated counterclockwise by the specified number of degrees around the origin of its bounding box. If the rotation angle is 90 or 270 degrees, the height (width) of the resulting shape is equal to the width (height) of the original shape.

* **Scaled(Shape shape, double fx, double fy).** Takes a shape, a horizontal scaling factor fx, and a vertical scaling factor fy. Creates a version of the shape that is scaled horizontally and vertically by the given scaling factors.

* **Layered(Shape... shapes).** Given a collection of shapes, creates a new shape consisting of all the shapes drawn with their bounding boxes centered around the current point. The height and width of a layered shape is the maximum of the heights and widths of the component shapes.

* **Vertical(Shape... shapes).** Takes an ordered collection of shapes, and creates a shape structured as follows:
*	Shape shapes[i+1]'s bounding box is located directly above the bounding box of shapes[i], and both bounding boxes are vertically aligned around their center.
*	The height of the resulting shape's bounding box is the sum of the heights of the component shapes.
*	The width of the resulting shape's bounding box is the maximum width of the widths of the component shapes.

* **Horizontal(Shape... shapes).** Takes an ordered collection of shapes, and creates a shape structured as follows:
*	Shape shapes[i+1]'s bounding box is located next to (to the right of) the bounding box of shapes[i], and both bounding boxes are horizontally aligned around their center.
*	The width of the resulting shape's bounding box is the sum of the widths of the component shapes.
*	The height of the resulting shape's bounding box is the maximum width of the heights of the component shapes.

### CPS to PostScript translator
CPS lets the user translate any shape into a sequence of PostScript commands. The user can specify the name of the resulting file. The resulting file is a legal PostScript file that can be previewed on screen or printed on paper.

## Tasks
1. Formalize the shape language as one or more recursive type definitions.
2. Design and implement CPS.
3. Design one or more nice shapes of your own and generate PostScript from them. You'll probably want to write some classes that build on the shape language. For example, you might implement a class Skylines that contains methods returning randomized skylines with the number/height/shape of buildings specified as input arguments to the methods. Or you might implement a class Fractals that creates some fractal figures with a recursion limit specified by the user. These are just examples; it's entirely up to you. A prize will be awarded for the best shape.
4. Design and implement a test strategy for this project. In addition to the test cases themselves, you should give a brief commentary explaining your strategy.
5. Critique the specification of the shape language. Is the language expressive enough to create interesting drawings? Are the shape abstractions well-designed, or not? Do they make certain drawings easy/difficult to create? If you were to design the shape language from scratch, what would you do differently?

## Hints
1. The standard way to structure an implementation of a language is to have a collection of classes for representing the syntactic objects of the language (in this case, the shapes), and some functions that perform operations with these objects. For CPS, these operations might compute the width and height of a shape, and convert a shape into a PostScript program.
2. The "..." syntax in the compound shape definitions above is meant to represent "any number of." You will need to implement this as some sort of C++ container. (I'd recommend just having a constructor that takes an initializer_list.)
3. When implementing a function that generates a PostScript program, it may be useful to (1) assume, on entry to each visiting method, that the point around which the shape is to be centered has already been correctly set; and (2) for basic shapes, to draw the shape by starting a new path, drawing, closing the path, and calling stroke; and (3) for some operation methods, to use gsave on entry and grestore before exit. These are only suggestions, however, and you might find a different (and maybe better) approach.
4. The width and height of the bounding box for Polygon(numberOfSides, sideLength) is given by the following formulas:

*	**Case 1:** numberOfSides is *odd*.

*		height = sideLength(1+cos(π/numberOfSides))/(2sin(π/numberOfSides))
*		width = (sideLength sin(π(numberOfSides-1)/2n))/(sin(π/numberOfSides))

*	**Case 2:** numberOfSides is divisible by 4.

*		height = sideLength(cos(π/numberOfSides))/(sin(π/numberOfSides))
*		width = (sideLength cos(π/numberOfSides))/(sin(π/numberOfSides))

*	**Case 3:** numberOfSides is divisible by 2, but not by 4.

*		height = sideLength(cos(π/numberOfSides))/(sin(π/numberOfSides))
*		width = sideLength /(sin(π/numberOfSides))

5. In PostScript, use showpage to finally draw the current page and create a new page.

## Files
The following files are included with this package:
*	[CompoundShapes.cpp](https://github.com/FizzyGalacticus/Project-2/blob/master/CompoundShapes.cpp)
*	[CompoundShapes.h](https://github.com/FizzyGalacticus/Project-2/blob/master/CompoundShapes.h)
*	[translator.cpp](https://github.com/FizzyGalacticus/Project-2/blob/master/translator.cpp)
*	[README.md](https://github.com/FizzyGalacticus/Project-2/blob/master/README.md)
*	[Shapes.cpp](https://github.com/FizzyGalacticus/Project-2/blob/master/Shapes.cpp)
*	[Shapes.h](https://github.com/FizzyGalacticus/Project-2/blob/master/Shapes.h)
*	[testShapes.cpp](https://github.com/FizzyGalacticus/Project-2/blob/master/testShapes.cpp)

## Use
To use this library, you can create a Shape object by passing the correct variables to their constructors (please see source regarding constructor arguments). Once an object is created, you can get the appropriate PostScript code as an std::string from the object by calling its draw() method.

To compile the library, you must include the Shapes.h and CompoundShapes.h files, then link with Shapes.cpp and CompoundShapes.cpp.

**NOTE** You must compile using the c++11 standard. We make good use of shared_ptr and the 'auto' keyword.

"translator.cpp", when compiled, is a driver demo for creating as many shapes as you want in whatever order you want, then manipulating them. You can run it with no arguments, or the first argument you pass it will be the output file name. It functions essentially just like a stack-based language, meaning that each shape is added in the order that you make them. By making a layered, vertical, or horizontal shape, it takes every shape from the "stack" and puts them into the new Compound Shape (once again, in the order they were created). Choosing to rotate a shape is choosing to rotate all of the shapes on the "stack." You can add multiple pages as you go, each time you do, it empties the current "stack." Telling the demo that you are done with the shapes also writes to a page, then writes to the file.
