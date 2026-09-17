#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <array>
#include <string>
#include <cstdint>
#include <iomanip>
#include <clocale>
#include <iterator>
#include <algorithm>
#include <memory>

using namespace std;

struct Node
{
    unsigned char symbol;
    uint64_t frequency;

    unsigned char minSymbol;

    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(unsigned char s, uint64_t f)
        : symbol(s),
        frequency(f),
        minSymbol(s),
        left(nullptr),
        right(nullptr)
    {
    }

    Node(shared_ptr<Node> l, shared_ptr<Node> r)
        : symbol(0),
        frequency(l->frequency + r->frequency),
        minSymbol(min(l->minSymbol, r->minSymbol)),
        left(move(l)),
        right(move(r))
    {
    }

    bool isLeaf() const
    {
        return left == nullptr && right == nullptr;
    }
};

using NodePtr = shared_ptr<Node>;


struct Compare
{
    bool operator()(const NodePtr& a, const NodePtr& b) const
    {
        if (a->frequency != b->frequency)
        {
            return a->frequency > b->frequency;
        }
        return a->minSymbol > b->minSymbol;
    }
};


using FreqTable = array<uint64_t, 256>;
using CodeTable = array<string, 256>;


FreqTable calculateFrequencies(const vector<unsigned char>& data)
{
    FreqTable frequencies{};
    frequencies.fill(0);

    for (unsigned char c : data)
    {
        frequencies[c]++;
    }

    return frequencies;
}


NodePtr buildTree(const FreqTable& frequencies)
{
    priority_queue<NodePtr, vector<NodePtr>, Compare> pq;

    for (size_t i = 0; i < frequencies.size(); ++i)
    {
        if (frequencies[i] == 0)
            continue;

        pq.push(make_shared<Node>(
            static_cast<unsigned char>(i),
            frequencies[i]));
    }

    if (pq.empty())
        return nullptr;

    if (pq.size() == 1)
    {
        NodePtr only = pq.top();
        pq.pop();

        NodePtr emptyNode = make_shared<Node>(
            static_cast<unsigned char>(0), 0);

        return make_shared<Node>(only, emptyNode);
    }

    while (pq.size() > 1)
    {
        NodePtr left = pq.top(); pq.pop();
        NodePtr right = pq.top(); pq.pop();

        pq.push(make_shared<Node>(left, right));
    }

    return pq.top();
}


void buildCodes(
    const NodePtr& root,
    const string& code,
    CodeTable& codes)
{
    if (!root)
        return;

    if (root->isLeaf())
    {
        codes[root->symbol] = code.empty() ? "0" : code;
        return;
    }

    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}


void writeUint64(ofstream& out, uint64_t value)
{
    out.write(
        reinterpret_cast<const char*>(&value),
        sizeof(value));
}

bool readUint64(ifstream& in, uint64_t& value)
{
    return static_cast<bool>(
        in.read(
            reinterpret_cast<char*>(&value),
            sizeof(value)));
}


bool encodeFile(
    const string& inputFile,
    const string& outputFile)
{
    ifstream in(inputFile, ios::binary);
    if (!in)
    {
        cerr << "Ошибка: не удалось открыть исходный файл.\n";
        return false;
    }

    vector<unsigned char> data(
        (istreambuf_iterator<char>(in)),
        istreambuf_iterator<char>());
    in.close();

    if (data.empty())
    {
        cerr << "Ошибка: исходный файл пуст.\n";
        return false;
    }

    FreqTable frequencies = calculateFrequencies(data);

    NodePtr root = buildTree(frequencies);
    if (!root)
    {
        cerr << "Ошибка: не удалось построить дерево.\n";
        return false;
    }

    CodeTable codes;
    buildCodes(root, "", codes);

    ofstream out(outputFile, ios::binary);
    if (!out)
    {
        cerr << "Ошибка: не удалось создать выходной файл.\n";
        return false;
    }

    uint64_t originalSize = static_cast<uint64_t>(data.size());

    uint64_t uniqueSymbols = 0;
    for (uint64_t f : frequencies)
        if (f > 0) ++uniqueSymbols;

    writeUint64(out, originalSize);
    writeUint64(out, uniqueSymbols);

    for (size_t i = 0; i < frequencies.size(); ++i)
    {
        if (frequencies[i] == 0)
            continue;

        unsigned char symbol = static_cast<unsigned char>(i);

        out.write(
            reinterpret_cast<const char*>(&symbol),
            sizeof(symbol));

        writeUint64(out, frequencies[i]);
    }

    unsigned char buffer = 0;
    int bitCount = 0;

    for (unsigned char c : data)
    {
        const string& code = codes[c];

        for (char bit : code)
        {
            buffer <<= 1;
            if (bit == '1')
                buffer |= 1;

            ++bitCount;

            if (bitCount == 8)
            {
                out.write(
                    reinterpret_cast<const char*>(&buffer),
                    sizeof(buffer));

                buffer = 0;
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0)
    {
        buffer <<= (8 - bitCount);

        out.write(
            reinterpret_cast<const char*>(&buffer),
            sizeof(buffer));
    }

    out.close();

    ifstream compressed(outputFile, ios::binary | ios::ate);
    uint64_t compressedSize =
        static_cast<uint64_t>(compressed.tellg());
    compressed.close();

    double coefficient =
        static_cast<double>(compressedSize) /
        static_cast<double>(originalSize);
    double savings = (1.0 - coefficient) * 100.0;

    cout << "\n========================================\n";
    cout << "       РЕЗУЛЬТАТ КОДИРОВАНИЯ\n";
    cout << "========================================\n";
    cout << "Исходный размер: " << originalSize << " байт\n";
    cout << "Сжатый размер:   " << compressedSize << " байт\n";
    cout << fixed << setprecision(2);
    cout << "Коэффициент:     " << coefficient << "\n";
    cout << "Экономия:         " << savings << "%\n";
    cout << "Выходной файл:   " << outputFile << "\n";
    cout << "========================================\n";

    return true;
}


bool decodeFile(
    const string& inputFile,
    const string& outputFile)
{
    ifstream in(inputFile, ios::binary);
    if (!in)
    {
        cerr << "Ошибка: не удалось открыть сжатый файл.\n";
        return false;
    }

    uint64_t originalSize = 0;
    uint64_t uniqueSymbols = 0;

    if (!readUint64(in, originalSize) ||
        !readUint64(in, uniqueSymbols))
    {
        cerr << "Ошибка: не удалось прочитать заголовок.\n";
        return false;
    }

    if (uniqueSymbols > 256)
    {
        cerr << "Ошибка: повреждённый файл.\n";
        return false;
    }

    FreqTable frequencies{};
    frequencies.fill(0);

    for (uint64_t i = 0; i < uniqueSymbols; ++i)
    {
        unsigned char symbol;
        uint64_t frequency;

        if (!in.read(
            reinterpret_cast<char*>(&symbol),
            sizeof(symbol)))
        {
            cerr << "Ошибка чтения символа.\n";
            return false;
        }

        if (!readUint64(in, frequency))
        {
            cerr << "Ошибка чтения частоты.\n";
            return false;
        }

        frequencies[symbol] = frequency;
    }

    NodePtr root = buildTree(frequencies);
    if (!root)
    {
        cerr << "Ошибка: дерево Хаффмана пусто.\n";
        return false;
    }

    ofstream out(outputFile, ios::binary);
    if (!out)
    {
        cerr << "Ошибка: не удалось создать восстановленный файл.\n";
        return false;
    }

    vector<unsigned char> decoded;
    decoded.reserve(static_cast<size_t>(originalSize));

    if (uniqueSymbols == 1)
    {
        for (size_t i = 0; i < frequencies.size(); ++i)
        {
            if (frequencies[i] > 0)
            {
                unsigned char symbol =
                    static_cast<unsigned char>(i);

                for (uint64_t k = 0; k < frequencies[i]; ++k)
                    decoded.push_back(symbol);

                break;
            }
        }
    }
    else
    {
        Node* current = root.get();
        unsigned char byte;

        while (in.read(
            reinterpret_cast<char*>(&byte),
            sizeof(byte)))
        {
            for (int i = 7; i >= 0; --i)
            {
                int bit = (byte >> i) & 1;

                current = (bit == 0)
                    ? current->left.get()
                    : current->right.get();

                if (!current)
                {
                    cerr << "Ошибка: повреждённые данные.\n";
                    return false;
                }

                if (current->isLeaf())
                {
                    decoded.push_back(current->symbol);
                    current = root.get();

                    if (decoded.size() ==
                        static_cast<size_t>(originalSize))
                        break;
                }
            }

            if (decoded.size() ==
                static_cast<size_t>(originalSize))
                break;
        }
    }

    for (unsigned char c : decoded)
        out.write(
            reinterpret_cast<const char*>(&c),
            sizeof(c));

    out.close();
    in.close();

    bool ok = (decoded.size() ==
        static_cast<size_t>(originalSize));

    cout << "\n========================================\n";
    cout << "       РЕЗУЛЬТАТ ДЕКОДИРОВАНИЯ\n";
    cout << "========================================\n";
    cout << "Восстановлено: " << decoded.size() << " байт\n";
    cout << "Ожидалось:     " << originalSize << " байт\n";
    cout << "Выходной файл: " << outputFile << "\n";
    cout << "Статус:        "
        << (ok ? "УСПЕШНО" : "ОШИБКА") << "\n";
    cout << "========================================\n";

    return ok;
}


int main()
{
    setlocale(LC_ALL, "");

    cout << "========================================\n";
    cout << "          КОДЫ ХАФФМАНА\n";
    cout << "          Курсовая работа\n";
    cout << "========================================\n";

    while (true)
    {
        cout << "\n";
        cout << "1. Закодировать файл\n";
        cout << "2. Декодировать файл\n";
        cout << "0. Выход\n";
        cout << "\nВыберите действие: ";

        int choice;
        cin >> choice;

        if (choice == 0)
        {
            cout << "Программа завершена.\n";
            break;
        }

        if (choice == 1)
        {
            string inputFile, outputFile;
            cout << "Введите имя исходного файла: ";
            cin >> inputFile;
            cout << "Введите имя сжатого файла: ";
            cin >> outputFile;
            encodeFile(inputFile, outputFile);
        }
        else if (choice == 2)
        {
            string inputFile, outputFile;
            cout << "Введите имя сжатого файла: ";
            cin >> inputFile;
            cout << "Введите имя восстановленного файла: ";
            cin >> outputFile;
            decodeFile(inputFile, outputFile);
        }
        else
        {
            cout << "Неверный пункт меню.\n";
        }
    }

    return 0;
}
