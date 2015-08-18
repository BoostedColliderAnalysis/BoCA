/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Configuration.hh"

#include <iostream>

namespace analysis {

Configuration::Configuration()
{
    ReadConfig("Standard");
}

Configuration::Configuration(std::string const& config_name)
{
    ReadConfig(config_name);
}

// in GeV
int Configuration::Mass() const
{
    return mass_;
}

// in GeV
int Configuration::PreCut() const
{
    return pre_cut_;
}

int Configuration::EventNumberMax() const
{
    return event_number_max_;
}

int Configuration::BackgroundFileNumber() const
{
    return background_file_number_;
}

ColliderType Configuration::collider_type() const
{
    return collider_type_;
}

// in GeV
int Configuration::Mass_()
{
    try {
        mass_ = config().lookup("Mass");
    } catch (const libconfig::SettingNotFoundException& SettingNotFoundException) {
        std::cerr << "No 'Mass' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException& SettingTypeException) {
        std::cerr << "'Mass' setting has wrong type." << std::endl;
        throw;
    }
    return mass_;
}

// in GeV
int Configuration::PreCut_()
{
    try {
        pre_cut_ = config().lookup("PreCut");
    } catch (const libconfig::SettingNotFoundException& SettingNotFoundException) {
        std::cerr << "No 'PreCut' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException& SettingTypeException) {
        std::cerr << "'PreCut' setting has wrong type." << std::endl;
        throw;
    }
    return pre_cut_;
}

int Configuration::EventNumberMax_()
{
    try {
        event_number_max_ = config().lookup("EventNumberMax");
    } catch (const libconfig::SettingNotFoundException& SettingNotFoundException) {
        std::cerr << "No 'EventNumberMax' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException& SettingTypeException) {
        std::cerr << "'EventNumberMax' setting has wrong type." << std::endl;
        throw;
    }
    return event_number_max_;
}

int Configuration::BackgroundFileNumber_()
{
    try {
        background_file_number_ = config().lookup("BackgroundFileNumber");
    } catch (const libconfig::SettingNotFoundException& SettingNotFoundException) {
        std::cerr << "No 'BackgroundFileNumber' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException& SettingTypeException) {
        std::cerr << "'BackgroundFileNumber' setting has wrong type." << std::endl;
        throw;
    }
    return background_file_number_;
}

ColliderType Configuration::ColliderType_()
{
    try {
        std::string Collider = config().lookup("ColliderType");
        if (Collider == "LHC")
          collider_type_ = ColliderType::LHC;
        else if (Collider == "LE")
          collider_type_ = ColliderType::LE;
        else if (Collider == "FHC")
          collider_type_ = ColliderType::FHC;
    } catch (const libconfig::SettingNotFoundException& SettingNotFoundException) {
        std::cerr << "No 'ColliderType' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException& SettingTypeException) {
        std::cerr << "'ColliderType' setting has wrong type." << std::endl;
        throw;
    }
    return ColliderType::LHC;
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
        std::cerr << "New configuration successfully written to: " << ConfigFile(config_name) << std::endl;
    } catch (const libconfig::FileIOException& FileIOException) {
        std::cerr << "I/O error while writing file: " << ConfigFile(config_name) << std::endl;
    }
}

void Configuration::ReadConfig(std::string const& config_name)
{
    try {
        config().readFile(ConfigFile(config_name).c_str());
    } catch (const libconfig::FileIOException& FileIOException) {
        std::cerr << "I/O error while reading file." << std::endl;
        WriteConfig(config_name);
    } catch (const libconfig::ParseException& ParseException) {
        std::cerr << "Parse error at " << ParseException.getFile() << ":" << ParseException.getLine() << " - " << ParseException.getError() << std::endl;
    }
    Mass_();
    PreCut_();
    EventNumberMax_();
    BackgroundFileNumber_();
    ColliderType_();
}
Configuration& Configuration::operator=(const Configuration& configuration)
{
    this->mass_ = configuration.mass_;
    this->pre_cut_ = configuration.pre_cut_;
    this->event_number_max_ = configuration.event_number_max_;
    this->background_file_number_ = configuration.background_file_number_;
    this->collider_type_ = configuration.collider_type_;
    return *this;
}
std::string Configuration::ConfigFile(std::string const& config_name)
{
    return config_name + ".cfg";
}

}

