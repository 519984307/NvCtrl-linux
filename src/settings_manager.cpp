#include <filesystem>
#include <iterator>

#include <QDebug>

#include "settings_manager.hpp"

const nlohmann::json SettingsManager::default_settings
{
    {"check_for_updates_on_startup", false},
    {"branch_where_get_updates", 0},
    {"minimize_to_tray_on_close", false},
    {"minimize_to_tray_on_startup", false},

    {"last_fan_profile_index", 0},
    {"last_fan_profile_saved", false},

    {"last_clock_offset_profile_index", 0},
    {"last_clock_offset_profile_saved", false},

    {"last_power_profile_value", 0},
    {"last_power_profile_saved", false},

    {"fan_speed_profiles", nlohmann::json::array_t { {{"name", "Auto (VBIOS controlled) (default)"}} } },
    {"clock_offset_profiles", nlohmann::json::array_t { {{"name", "None (default)"}} } },

    {"update_freq_ms", 1000}
};



void SettingsManager::write_settings(const nlohmann::json& app_settings)
{
    close_file();
    open_file(std::ios::in | std::ios::out | std::ios::trunc);
    settings_file_ << app_settings.dump(2);
    settings_file_.flush();
    qDebug().noquote().nospace() << "Saving settings to: " << file_name_.c_str();
}



nlohmann::json SettingsManager::read_settings()
{
    std::string raw_json_string {std::istreambuf_iterator<char>{settings_file_},
                                 std::istreambuf_iterator<char>{}};

    qDebug().noquote().nospace() << "Reading settings from: " << file_name_.c_str();

    auto app_settings = nlohmann::json::parse(std::move(raw_json_string));
    validate_settings(app_settings);

    return app_settings;
}



bool SettingsManager::file_is_open() const
{
    return settings_file_.is_open();
}



SettingsManager& SettingsManager::instance()
{
    static SettingsManager settings_manager {};
    return settings_manager;
}



SettingsManager::SettingsManager()
    : settings_file_ {}
    , file_name_ {}
{
    if (!std::filesystem::exists(get_home_dir()))
    {
        qDebug().noquote().nospace() << "Directory " << get_home_dir().c_str() << " doesn`t exists and will be created";
        std::filesystem::create_directory(get_home_dir());
    }

    file_name_ = get_home_dir() + "NvCtrl-Linux.json";

    if (!std::filesystem::exists(file_name_))
    {
        qDebug().noquote().nospace() << "File " << file_name_.c_str() << " doesn`t exists and will ge created";
        open_file(std::ios::out);
        write_settings(default_settings);
        close_file();
    }

    open_file(std::ios::in | std::ios::out);
}



SettingsManager::~SettingsManager()
{
    close_file();
}



void SettingsManager::open_file(std::ios::openmode open_mode)
{
    settings_file_.open(file_name_, open_mode);
}



void SettingsManager::close_file()
{
    settings_file_.close();
}



void SettingsManager::validate_settings(nlohmann::json& app_settings)
{
    bool something_was_invalid {false};

    auto& update_freq_ms {app_settings["update_freq_ms"]};
    auto& fan_speed_profiles {app_settings["fan_speed_profiles"]};
    auto& clock_offset_profiles {app_settings["clock_offset_profiles"]};

    if (update_freq_ms.is_null() || !update_freq_ms.is_number()
            || update_freq_ms < default_settings["update_freq_ms"])
    {
        update_freq_ms = default_settings["update_freq_ms"];
        something_was_invalid = true;
    }

    if (fan_speed_profiles.is_null() || !fan_speed_profiles.is_array())
    {
        fan_speed_profiles = default_settings["fan_speed_profiles"];
        something_was_invalid = true;
    }
    else if (fan_speed_profiles.empty()
            || fan_speed_profiles[0]["name"]
            != default_settings["fan_speed_profiles"][0]["name"])
    {
        fan_speed_profiles[0] = default_settings["fan_speed_profiles"][0];
        something_was_invalid = true;
    }

    if (clock_offset_profiles.is_null() || !clock_offset_profiles.is_array())
    {
        clock_offset_profiles = default_settings["clock_offset_profiles"];
        something_was_invalid = true;
    }
    else if (clock_offset_profiles.empty()
             || clock_offset_profiles[0]["name"]
             != default_settings["clock_offset_profiles"][0]["name"])
    {
        clock_offset_profiles[0] = default_settings["clock_offset_profiles"][0];
        something_was_invalid = true;
    }

    if (something_was_invalid)
    {
        write_settings(app_settings);
    }
}



const std::string& SettingsManager::get_home_dir() const
{
#ifdef _WIN32
    static const std::string home_dir {"C:\\Users\\" + std::string{std::getenv("USERNAME")} + "\\NvCtrl-Linux\\"};
#else
    static const std::string home_dir {"/home/" + std::string{std::getenv("USER")} + "/.config/NvCtrl-Linux/"};
#endif
    return home_dir;
}
