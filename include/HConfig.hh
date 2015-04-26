# ifndef HConfig_hh
# define HConfig_hh

# include "libconfig.h++"
enum HColliderType {LHC, FHC, LE};

class HConfig
{
public:

    HConfig() {
        config_ = new libconfig::Config;
        ReadConfig("Standard");
    }

    HConfig(const std::string &ConfigName) {
        config_ = new libconfig::Config;
        ReadConfig(ConfigName);
    }

    ~HConfig() {
//         delete config_; // Why?
    }

    // in GeV
    inline int Mass() const {
        return mass_;
    }

           // in GeV
    inline int PreCut() const {
        return pre_cut_;
    }

    inline int EventNumberMax() const {
        return event_number_max_;
    };

    inline int BackgroundFileNumber() const {
        return background_file_number_;
    }

    inline HColliderType ColliderType() const {
        return collider_type_;
    }
private:

    // in GeV
    inline int Mass_()  {
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
    inline int PreCut_()  {
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

    inline int EventNumberMax_()  {
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

    inline int BackgroundFileNumber_()  {
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

    inline HColliderType ColliderType_()  {
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


    void WriteConfig(const std::string &ConfigName) {
        std::string config_name = ConfigName + ".cfg";
//         std::string config_name = "Neutral.cfg";

        libconfig::Setting &root = config_->getRoot();
        libconfig::Setting &mass = root.add("Mass",  libconfig::Setting::TypeInt) = 1000;
        libconfig::Setting &pre_cut = root.add("PreCut",  libconfig::Setting::TypeInt) = 1000;
        libconfig::Setting &event_number_max = root.add("EventNumberMax",  libconfig::Setting::TypeInt) = 10000;
        libconfig::Setting &background_file_number = root.add("BackgroundFileNumber",  libconfig::Setting::TypeInt) = 1;
        libconfig::Setting &collider_type = root.add("ColliderType",  libconfig::Setting::TypeString) = "LE";
        try {
            config_->writeFile(config_name.c_str());
            std::cerr << "New configuration successfully written to: " << config_name << std::endl;
        } catch (const libconfig::FileIOException &FileIOException) {
            std::cerr << "I/O error while writing file: " << config_name << std::endl;
        }
    }

    void ReadConfig(const std::string &ConfigName) {
        try {
            std::string config_name = ConfigName + ".cfg";
//             std::string config_name = "Neutral.cfg";
            config_->readFile(config_name.c_str());
        } catch (const libconfig::FileIOException &FileIOException) {
            std::cerr << "I/O error while reading file." << std::endl;
            WriteConfig(ConfigName);
        } catch (const libconfig::ParseException &ParseException) {
            std::cerr << "Parse error at " << ParseException.getFile() << ":" << ParseException.getLine() << " - " << ParseException.getError() << std::endl;
        }
        Mass_();
        PreCut_();
        EventNumberMax_();
        BackgroundFileNumber_();
        ColliderType_();
    }

    libconfig::Config *config_;
    int mass_;
    int pre_cut_;
    int event_number_max_;
    int background_file_number_;
    HColliderType collider_type_;

};

# endif
