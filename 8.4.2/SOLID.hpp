#pragma once

class Printable
{
public:
    virtual ~Printable() = default;

    virtual void print() const = 0;
};

class AsHTML {
public:
    virtual std::string printHTML() const = 0;
};

class printAsHTML : public Printable, public AsHTML {
public:
    void print() const {
        printHTML();
    }
    virtual std::string printHTML() const = 0;
};

class AsText {
public:
    virtual std::string printText() const = 0;
};

class printAsText : public Printable, public AsText {
public:
    void print() const {
        printText();
    }
    virtual std::string printText() const = 0;
};

class AsJSON {
public:
    virtual std::string printJSON() const = 0;
};

class printAsJSON : public Printable, public AsJSON {
public:
    void print() const {
        printJSON();
    }
    virtual std::string printJSON() const = 0;
};


class Data : public printAsHTML, public printAsText, public printAsJSON
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

void saveToAsHTML(std::ofstream& file, const Data& data) {
    file << data.printHTML();
}

void saveToAsJSON(std::ofstream& file, const Data& data) {
    file << data.printJSON();
}

void saveToAsText(std::ofstream& file, const Data& data) {
    file << data.printText();
}