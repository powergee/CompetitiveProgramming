#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using Grid = std::vector<std::string>;

void drawHorLine(Grid& grid, int r, int c, int length) {
    for (int i = 0; i < length; ++i) {
        grid[r][c+i] = '-';
    }
}

void drawVerLine(Grid& grid, int r, int c, int length) {
    for (int i = 0; i < length; ++i) {
        grid[r+i][c] = '|';
    }
}

void drawHorArrow(Grid& grid, int r, int c, int length, bool toRight) {
    drawHorLine(grid, r, c, length);
    if (toRight) {
        grid[r][c+length-1] = '>';
    } else {
        grid[r][c] = '<';
    }
}

class Module;
class Input;
class Expression;
class Term;
class Atom;
class PlusEnvelope;
class QuestionEnvelope;
class StarEnvelope;

class Module {
public:
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual void pasteContents(Grid& grid, int r, int c) = 0;
    virtual bool isTerminal() = 0;
};

class Input : public Module {
private:
    Expression* root;

public:
    Input(std::string& s);
    int getWidth();
    int getHeight();
    void pasteContents(Grid& grid, int r, int c);
    bool isTerminal() { return false; }
};

class Expression : public Module {
private:
    std::vector<Term*> terms;

public:
    Expression(std::string& s, int& index);
    int getWidth();
    int getHeight();
    void pasteContents(Grid& grid, int r, int c);
    bool isTerminal() { return false; }
};

class Term : public Module {
private:
    std::vector<Module*> atoms;

public:
    Term(std::string& s, int& index);
    int getWidth();
    int getHeight();
    void pasteContents(Grid& grid, int r, int c);
    bool isTerminal() { return false; }
};

class Atom : public Module {
private:
    std::string label;
    Module* inner;

public:
    Atom(std::string& s, int& index);
    int getWidth();
    int getHeight();
    void pasteContents(Grid& grid, int r, int c);
    bool hasInnerModule();
    void append(Atom* atom);
    bool isTerminal() { return !hasInnerModule(); }
};

class PlusEnvelope : public Module {
private:
    Module* inner;

public:
    PlusEnvelope(Module* inner);
    int getWidth();
    int getHeight();
    void pasteContents(Grid& grid, int r, int c);
    bool isTerminal() { return false; }
};

class QuestionEnvelope : public Module {
private:
    Module* inner;

public:
    QuestionEnvelope(Module* inner);
    int getWidth();
    int getHeight();
    void pasteContents(Grid& grid, int r, int c);
    bool isTerminal() { return false; }
};

class StarEnvelope : public Module {
private:
    Module* inner;

public:
    StarEnvelope(Module* inner);
    int getWidth();
    int getHeight();
    void pasteContents(Grid& grid, int r, int c);
    bool isTerminal() { return false; }
};

StarEnvelope::StarEnvelope(Module* inner) {
    this->inner = inner;
}

int StarEnvelope::getWidth() {
    return inner->getWidth() + 6;
}

int StarEnvelope::getHeight() {
    return inner->getHeight() + 5;
}

void StarEnvelope::pasteContents(Grid& grid, int r, int c) {
    int w = getWidth();
    int h = getHeight();

    // Corners
    grid[r+1][c] = grid[r+1][c+w-1] = '+';
    grid[r+4][c] = grid[r+4][c+w-1] = '+';
    grid[r+h-1][c] = grid[r+h-1][c+w-1] = '+';
    
    // Arrows
    drawHorArrow(grid, r+1, c+1, w-2, true);
    drawHorArrow(grid, r+4, c+1, 2, true);
    drawHorArrow(grid, r+4, c+w-3, 2, true);
    drawHorArrow(grid, r+h-1, c+1, w-2, false);

    // Ver Lines
    drawVerLine(grid, r+2, c, 2);
    drawVerLine(grid, r+5, c, h-6);
    drawVerLine(grid, r+2, c+w-1, 2);
    drawVerLine(grid, r+5, c+w-1, h-6);

    inner->pasteContents(grid, r+3, c+3);
}

QuestionEnvelope::QuestionEnvelope(Module* inner) {
    this->inner = inner;
}

int QuestionEnvelope::getWidth() {
    return inner->getWidth() + 6;
}

int QuestionEnvelope::getHeight() {
    return inner->getHeight() + 3;
}

void QuestionEnvelope::pasteContents(Grid& grid, int r, int c) {
    int w = getWidth();
    int h = getHeight();

    // Corners
    grid[r+1][c] = grid[r+1][c+w-1] = '+';
    grid[r+4][c] = grid[r+4][c+w-1] = '+';
    
    // Arrows
    drawHorArrow(grid, r+1, c+1, w-2, true);
    drawHorArrow(grid, r+4, c+1, 2, true);
    drawHorArrow(grid, r+4, c+w-3, 2, true);

    // Ver Lines
    drawVerLine(grid, r+2, c, 2);
    drawVerLine(grid, r+2, c+w-1, 2);

    inner->pasteContents(grid, r+3, c+3);
}

PlusEnvelope::PlusEnvelope(Module* inner) {
    this->inner = inner;
}

int PlusEnvelope::getWidth() {
    return inner->getWidth() + 6;
}

int PlusEnvelope::getHeight() {
    return inner->getHeight() + 2;
}

void PlusEnvelope::pasteContents(Grid& grid, int r, int c) {
    int subW = inner->getWidth();
    int subH = inner->getHeight();

    // Corners
    grid[r+1][c] = grid[r+1][c+subW+5] = '+';
    grid[r+1+subH][c] = grid[r+1+subH][c+subW+5] = '+';
    
    // Arrows
    drawHorArrow(grid, r+1+subH, c+1, subW+4, false);
    drawHorArrow(grid, r+1, c+1, 2, true);
    drawHorArrow(grid, r+1, c+subW+3, 2, true);

    // Ver Lines
    drawVerLine(grid, r+2, c, subH-1);
    drawVerLine(grid, r+2, c+subW+5, subH-1);

    inner->pasteContents(grid, r, c+3);
}

Atom::Atom(std::string& s, int& index) {
    if (s[index] == '(') {
        ++index;
        inner = new Expression(s, index);
        ++index;
    } else {
        label = s[index++];
        inner = nullptr;
    }
}

int Atom::getWidth() {
    if (hasInnerModule()) {
        return inner->getWidth();
    } else {
        return label.size() + 4;
    }
}

int Atom::getHeight() {
    if (hasInnerModule()) {
        return inner->getHeight();
    } else {
        return 3;
    }
}

void Atom::pasteContents(Grid& grid, int r, int c) {
    if (hasInnerModule()) {
        return inner->pasteContents(grid, r, c);
    } else {
        int w = getWidth();
        int h = getHeight();

        drawHorLine(grid, r, c, w);
        drawHorLine(grid, r+2, c, w);

        grid[r][c] = grid[r+1][c] = grid[r+2][c] = '+';
        grid[r][c+w-1] = grid[r+1][c+w-1] = grid[r+2][c+w-1] = '+';

        for (int i = 0; i < label.size(); ++i) {
            grid[r+1][c+2+i] = label[i];
        }
    }
}

bool Atom::hasInnerModule() {
    return inner != nullptr;
}

void Atom::append(Atom* atom) {
    label += atom->label;
}

Term::Term(std::string& s, int& index) {
    std::vector<Module*> units;
    while (index < s.size() && s[index] != '|' && s[index] != ')') {
        if (s[index] == '+') {
            Module* inner = units.back();
            units.back() = new PlusEnvelope(inner);
            ++index;
        } else if (s[index] == '?') {
            Module* inner = units.back();
            units.back() = new QuestionEnvelope(inner);
            ++index;
        } else if (s[index] == '*') {
            Module* inner = units.back();
            units.back() = new StarEnvelope(inner);
            ++index;
        } else {
            Atom* curr = new Atom(s, index);
            units.push_back(curr);
        }
    }

    atoms.push_back(units[0]);
    for (int i = 1; i < units.size(); ++i) {
        if (atoms.back()->isTerminal() && units[i]->isTerminal()) {
            Atom* prev = dynamic_cast<Atom*>(atoms.back());
            Atom* curr = dynamic_cast<Atom*>(units[i]);
            prev->append(curr);
            delete curr;
        } else {
            atoms.push_back(units[i]);
        }
    }
}

int Term::getWidth() {
    int total = 0;
    for (Module* atom : atoms) {
        total += atom->getWidth();
    }
    total += 2 * (int(atoms.size())-1);
    return total;
}

int Term::getHeight() {
    int max = 0;
    for (Module* atom : atoms) {
        max = std::max(max, atom->getHeight());
    }
    return max;
}

void Term::pasteContents(Grid& grid, int r, int c) {
    int currC = c;

    for (int i = 0; i < atoms.size(); ++i) {
        atoms[i]->pasteContents(grid, r, currC);
        if (i+1 < atoms.size()) {
            drawHorArrow(grid, r+1, currC+atoms[i]->getWidth(), 2, true);
            currC += atoms[i]->getWidth()+2;
        }
    }
}

Expression::Expression(std::string& s, int& index) {
    while (index < s.size() && s[index] != ')') {
        if (s[index] == '|') {
            ++index;
        }
        terms.push_back(new Term(s, index));
    }
}

int Expression::getWidth() {
    if (terms.size() == 1) {
        return terms[0]->getWidth();
    }
    int maxWidth = 0;
    for (Term* term : terms) {
        maxWidth = std::max(maxWidth, term->getWidth());
    }
    return maxWidth + 6;
}

int Expression::getHeight() {
    int total = 0;
    for (Term* term : terms) {
        total += term->getHeight();
    }
    total += int(terms.size())-1;
    return total;
}

void Expression::pasteContents(Grid& grid, int r, int c) {
    if (terms.size() == 1) {
        terms[0]->pasteContents(grid, r, c);
    } else {
        int w = getWidth();
        int h = getHeight();
        int prevR = -1, currR = r;

        for (Term* term : terms) {
            int subW = term->getWidth();
            int subH = term->getHeight();

            term->pasteContents(grid, currR, c+3);
            drawHorArrow(grid, currR+1, c, 3, true);
            drawHorArrow(grid, currR+1, c+3+subW, w-4-subW, true);

            grid[currR+1][c] = grid[currR+1][c+w-1] = '+';

            if (prevR != -1) {
                drawVerLine(grid, prevR+2, c, currR-prevR-1);
                drawVerLine(grid, prevR+2, c+w-1, currR-prevR-1);
            }
            prevR = currR;
            currR += subH+1;
        }
    }
}

Input::Input(std::string& s) {
    int index = 0;
    root = new Expression(s, index);
}

int Input::getWidth() {
    return root->getWidth() + 6;
}

int Input::getHeight() {
    return root->getHeight();
}

void Input::pasteContents(Grid& grid, int r, int c) {
    int subW = root->getWidth();
    grid[r+1][c] = 'S';
    drawHorArrow(grid, r+1, c+1, 2, true);
    drawHorArrow(grid, r+1, c+3+subW, 2, true);
    grid[r+1][c+subW+5] = 'F';
    root->pasteContents(grid, r, c+3);
}

int main() {
    std::string source;
    std::getline(std::cin, source);
    Input* input = new Input(source);

    int w = input->getWidth();
    int h = input->getHeight();
    std::cout << h << " " << w << "\n";

    Grid grid(h, std::string(w, ' '));
    input->pasteContents(grid, 0, 0);
    
    for (std::string& row : grid) {
        std::cout << row << "\n";
    }

    return 0;
}