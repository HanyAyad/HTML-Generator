# HTML-generator-in-C++
A project to provide simple way to generate HTML code in C++ by creating objects of these tag classes and writing them to an ostream.

The project is a simple implementation of a HTML generator in C++. It defines a set of structs such as HEAD, BODY, TITLE, H1, META, and P, which correspond to different HTML tags. These structs inherit from a common Tag struct, which has basic information such as name, text, children tags, and attributes. The structs also overload the << operator to allow for easy output to a file stream.

The main function creates instances of the different HTML tags and constructs a basic HTML page with a title, headers, paragraphs, and meta information. The final page is saved to a file called "example.html".
