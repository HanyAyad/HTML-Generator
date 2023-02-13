#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <tuple>
#include <cstdio>
#include <utility>

using namespace std;

struct Attribute
{
    string name;
    string value;

    Attribute(const string& name, const string& value)
        : name(name), value(value) {}
};

struct Tag
{
    string name;
    string text;
    vector<Tag> children;
    vector<Attribute> attributes;

    friend ostream& operator<<(ostream& os, const Tag& tag)
    {
        os << "<" << tag.name;

        for (const auto& att : tag.attributes)
        {
            os << " " << att.name << "=\"" << att.value << "\"";
        }

        if (tag.children.size() == 0 && tag.text.length() == 0)
        {
            os << "/>" << endl;
        }
        else
        {
            os << ">" << endl;

            if (tag.text.length())
                os << tag.text << endl;

            for (const auto& child : tag.children)
                os << child;

            os << "</" << tag.name << ">" << endl;
        }

        return os;
    }

protected:
    Tag(const string& name, const string& text, const vector<Attribute>& attributes)
        : name(name), text(text), attributes(attributes) {}

public:
    Tag(const string& name, const string& text)
        : Tag(name, text, {}) {}

    Tag(const string& name, const vector<Tag>& children, const vector<Attribute>& attributes = {})
        : name(name), children(children), attributes(attributes) {}
};

struct HEAD : Tag
{
    HEAD(const vector<Tag>& children)
        : Tag("head", children) {}
};

struct BODY : Tag
{
    BODY(const vector<Tag>& children)
        : Tag("body", children) {}
};

struct TITLE : Tag
{
    TITLE(const string& text)
        : Tag("title", text) {}
};

struct H1 : Tag
{
    H1(const string& text)
        : Tag("h1", text) {}
};

struct META : Tag
{
    META(const string& name, const string& content)
        : Tag("meta", "", {Attribute("name", name), Attribute("content", content)}) {}
};

struct P : Tag
{
    P(const string& text)
        : Tag("p", text) {}

    P(initializer_list<Tag> children)
        :Tag("p", children) {}
};

int main()
{
H1 h1("Example Page");
P p1("This is an example page.");
P p2({"This is some text inside a paragraph.",
H1("A nested H1 heading."),
P("This is a nested paragraph.")});
META meta1("description", "An example page");
META meta2("keywords", "example, page");
TITLE title("Example Page");
HEAD head({title, meta1, meta2});

BODY body({h1, p1, p2});

ofstream out("example.html");
out << "<!DOCTYPE html>" << endl;
out << head << body;
out.close();

return 0;
