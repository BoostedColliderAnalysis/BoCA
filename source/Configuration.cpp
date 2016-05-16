/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Configuration.hh"
#include "boca/generic/DEBUG.hh"


namespace boca {

Configuration::Configuration()
{
    ReadConfig("Standard");
}

Configuration::Configuration(std::string const& config_name)
{
    ReadConfig(config_name);
}

boca::Mass Configuration::Mass()
{
    try {
        return static_cast<double>(config().lookup("Mass")) * GeV;
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        ERROR("No 'Mass' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        ERROR("'Mass' setting has wrong type");
        throw;
    }
}

Momentum Configuration::PreCut()
{
    try {
        return static_cast<double>(config().lookup("PreCut")) * GeV;
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        ERROR("No 'PreCut' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        ERROR("'PreCut' setting has wrong type");
        throw;
    }
}

long Configuration::TrainNumberMax()
{
    try {
        return config().lookup("EventNumberMax");
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        ERROR("No 'EventNumberMax' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        ERROR("'EventNumberMax' setting has wrong type");
        throw;
    }
}

int Configuration::BackgroundFileNumber()
{
    try {
        return config().lookup("BackgroundFileNumber");
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        ERROR("No 'BackgroundFileNumber' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        ERROR("'BackgroundFileNumber' setting has wrong type");
        throw;
    }
}

ColliderType Configuration::ColliderType()
{
    try {
        std::string Collider = config().lookup("ColliderType");
        if (Collider == "LHC") return boca::ColliderType::lhc;
        else if (Collider == "LE") return boca::ColliderType::future;
        else if (Collider == "FHC") return boca::ColliderType::FHC;
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        ERROR("No 'ColliderType' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        ERROR("'ColliderType' setting has wrong type");
        throw;
    }
    return boca::ColliderType::lhc;
}

void Configuration::WriteConfig(std::string const& config_name)
{
    libconfig::Setting& root = config().getRoot();
    libconfig::Setting& mass = root.add("Mass",  libconfig::Setting::TypeInt) = 1000;
    libconfig::Setting& pre_cut = root.add("PreCut",  libconfig::Setting::TypeInt) = 1000;
    libconfig::Setting& event_number_max = root.add("EventNumberMax",  libconfig::Setting::TypeInt) = 10000;
    libconfig::Setting& background_file_number = root.add("BackgroundFileNumber",  libconfig::Setting::TypeInt) = 1;
    libconfig::Setting& collider_type = root.add("ColliderType",  libconfig::Setting::TypeString) = "LE";
    try {
        config().writeFile(ConfigFile(config_name).c_str());
        ERROR("New configuration successfully written to", ConfigFile(config_name));
    } catch (libconfig::FileIOException const& file_io_exception) {
        ERROR("I/O error while writing file", ConfigFile(config_name));
    }
}

void Configuration::ReadConfig(std::string const& config_name)
{
    try {
        config().readFile(ConfigFile(config_name).c_str());
    } catch (libconfig::FileIOException const& file_io_exception) {
        ERROR("I/O error while reading file");
        WriteConfig(config_name);
    } catch (const libconfig::ParseException& ParseException) {
        ERROR("Parse error at", ParseException.getFile(), ParseException.getLine(), ParseException.getERROR());
    }
}

std::string Configuration::ConfigFile(std::string const& config_name)
{
    return config_name + ".cfg";
}

}

