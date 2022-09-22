#include <filesystem>
#include <fstream>
#include <memory>

int main()
{
    std::filesystem::path directory = "./data/";
    if (!exists(directory))
        return 1;

    if (!is_directory(directory))
        return 2;

    for (const auto& item : std::filesystem::directory_iterator(directory))
    {
        if (item.is_directory())
            continue;
        
        std::ifstream file(item.path(), std::ios::binary);
        file.seekg(0, std::ios::end);

        const std::size_t size = file.tellg();
        auto bytes = std::make_unique<char[]>(size);

        file.seekg(0);
        file.read(bytes.get(), size);
        file.close();

        // change script version number
        bytes[4] = 0xA;

        std::ofstream out(item.path(), std::ios::binary);
        out.write(bytes.get(), size);
        out.close();
    }

    return 0;
}