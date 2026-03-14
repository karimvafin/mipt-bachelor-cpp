#include <iostream>
#include <cstdint>
#include <type_traits>

// ── 1. Явный базовый тип ─────────────────────────────────────────────────────
// Базовый тип можно задать для enum и enum class.
// По умолчанию — int (4 байта). Можно использовать любой целочисленный тип.

enum class Status : uint8_t {
    Idle    = 0,
    Running = 1,
    Paused  = 2,
    Stopped = 3
};

// std::underlying_type_t<E> возвращает базовый тип перечисления.
void print_status_raw(Status s) {
    using T = std::underlying_type_t<Status>;  // uint8_t
    std::cout << "Status raw value: " << static_cast<int>(static_cast<T>(s)) << "\n";
}

// ── 2. Битовые флаги ─────────────────────────────────────────────────────────
// Перечислители задаются как степени двойки, чтобы каждый занимал отдельный бит.
// Флаги комбинируются через | и проверяются через &.

enum class Permission : uint8_t {
    None    = 0,
    Read    = 1 << 0,  // 0b00000001 = 1
    Write   = 1 << 1,  // 0b00000010 = 2
    Execute = 1 << 2,  // 0b00000100 = 4
};

// Операторы для удобной работы с флагами
Permission operator|(Permission a, Permission b) {
    using T = std::underlying_type_t<Permission>;
    return static_cast<Permission>(static_cast<T>(a) | static_cast<T>(b));
}

Permission operator&(Permission a, Permission b) {
    using T = std::underlying_type_t<Permission>;
    return static_cast<Permission>(static_cast<T>(a) & static_cast<T>(b));
}

bool has_permission(Permission set, Permission flag) {
    return (set & flag) != Permission::None;
}

// ── 3. switch и полнота ветвей ────────────────────────────────────────────────
// Компилятор с флагом -Wswitch предупреждает, если не все перечислители
// покрыты ветками switch. Это помогает не пропустить новые значения.

enum class Season { Spring, Summer, Autumn, Winter };

const char* season_to_str(Season s) {
    switch (s) {
        case Season::Spring: return "Spring";
        case Season::Summer: return "Summer";
        case Season::Autumn: return "Autumn";
        case Season::Winter: return "Winter";
        // Нет default: компилятор предупредит, если добавить новый Season
    }
    return "Unknown";
}


int main() {
    // 1. Базовый тип
    std::cout << "=== Underlying type ===\n";
    std::cout << "sizeof(Status): " << sizeof(Status) << " byte(s)\n";  // 1
    print_status_raw(Status::Running);

    // 2. Битовые флаги
    std::cout << "\n=== Bit flags ===\n";
    Permission perms = Permission::Read | Permission::Write | Permission::Execute;

    std::cout << "Has Read: "    << has_permission(perms, Permission::Read)    << "\n";  // 1
    std::cout << "Has Write: "   << has_permission(perms, Permission::Write)   << "\n";  // 1
    std::cout << "Has Execute: " << has_permission(perms, Permission::Execute) << "\n";  // 0

    // Добавить Execute
    perms = perms | Permission::Execute;
    std::cout << "After adding Execute: " << has_permission(perms, Permission::Execute) << "\n";  // 1

    return 0;
}
