# include "Configuration.hh"

analysis::Configuration::Configuration()
{
    config_ = new libconfig::Config;
    ReadConfig("Standard");
}

analysis::Configuration::Configuration(const std::string &config_name)
{
    config_ = new libconfig::Config;
    ReadConfig(config_name);
}

analysis::Configuration::~Configuration()
{
    delete config_;
}

// in GeV
int analysis::Configuration::Mass() const
{
    return mass_;
}

// in GeV
int analysis::Configuration::PreCut() const
{
    return pre_cut_;
}

int analysis::Configuration::EventNumberMax() const
{
    return event_number_max_;
};

int analysis::Configuration::BackgroundFileNumber() const
{
    return background_file_number_;
}

analysis::Configuration::ColliderType analysis::Configuration::collider_type() const
{
    return collider_type_;
}

// in GeV
int analysis::Configuration::Mass_()
{
    try {
        mass_ = config_->lookup("Mass");
    } catch (const libconfig::SettingNotFoundException &SettingNotFoundException) {
        std::cerr << "No 'Mass' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException &SettingTypeException) {
        std::cerr << "'Mass' setting has wrong type." << std::endl;
        throw;
    }
}

// in GeV
int analysis::Configuration::PreCut_()
{
    try {
        pre_cut_ = config_->lookup("PreCut");
    } catch (const libconfig::SettingNotFoundException &SettingNotFoundException) {
        std::cerr << "No 'PreCut' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException &SettingTypeException) {
        std::cerr << "'PreCut' setting has wrong type." << std::endl;
        throw;
    }
}

int analysis::Configuration::EventNumberMax_()
{
    try {
        event_number_max_ = config_->lookup("EventNumberMax");
    } catch (const libconfig::SettingNotFoundException &SettingNotFoundException) {
        std::cerr << "No 'EventNumberMax' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException &SettingTypeException) {
        std::cerr << "'EventNumberMax' setting has wrong type." << std::endl;
        throw;
    }
};

int analysis::Configuration::BackgroundFileNumber_()
{
    try {
        background_file_number_ = config_->lookup("BackgroundFileNumber");
    } catch (const libconfig::SettingNotFoundException &SettingNotFoundException) {
        std::cerr << "No 'BackgroundFileNumber' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException &SettingTypeException) {
        std::cerr << "'BackgroundFileNumber' setting has wrong type." << std::endl;
        throw;
    }
}

analysis::Configuration::ColliderType analysis::Configuration::ColliderType_()
{
    try {
        std::string Collider = config_->lookup("ColliderType");
        if (Collider == "LHC") collider_type_ = LHC;
        else if (Collider == "LE") collider_type_ = LE;
        else if (Collider == "FHC") collider_type_ = FHC;
    } catch (const libconfig::SettingNotFoundException &SettingNotFoundException) {
        std::cerr << "No 'ColliderType' setting in configuration file." << std::endl;
        throw;
    } catch (const libconfig::SettingTypeException &SettingTypeException) {
        std::cerr << "'ColliderType' setting has wrong type." << std::endl;
        throw;
    }
    return LHC;
}


void analysis::Configuration::WriteConfig(const std::string &config_name)
{
    std::string config_file = config_name + ".cfg";
//         std::string config_name = "Neutral.cfg";

    libconfig::Setting &root = config_->getRoot();
    libconfig::Setting &mass = root.add("Mass",  libconfig::Setting::TypeInt) = 1000;
    libconfig::Setting &pre_cut = root.add("PreCut",  libconfig::Setting::TypeInt) = 1000;
    libconfig::Setting &event_number_max = root.add("EventNumberMax",  libconfig::Setting::TypeInt) = 10000;
    libconfig::Setting &background_file_number = root.add("BackgroundFileNumber",  libconfig::Setting::TypeInt) = 1;
    libconfig::Setting &collider_type = root.add("ColliderType",  libconfig::Setting::TypeString) = "LE";
    try {
        config_->writeFile(config_file.c_str());
        std::cerr << "New configuration successfully written to: " << config_file << std::endl;
    } catch (const libconfig::FileIOException &FileIOException) {
        std::cerr << "I/O error while writing file: " << config_file << std::endl;
    }
}

void analysis::Configuration::ReadConfig(const std::string &config_name)
{
    try {
        std::string config_file = config_name + ".cfg";
//             std::string config_name = "Neutral.cfg";
        config_->readFile(config_file.c_str());
    } catch (const libconfig::FileIOException &FileIOException) {
        std::cerr << "I/O error while reading file." << std::endl;
        WriteConfig(config_name);
    } catch (const libconfig::ParseException &ParseException) {
        std::cerr << "Parse error at " << ParseException.getFile() << ":" << ParseException.getLine() << " - " << ParseException.getError() << std::endl;
    }
    Mass_();
    PreCut_();
    EventNumberMax_();
    BackgroundFileNumber_();
    ColliderType_();
}

