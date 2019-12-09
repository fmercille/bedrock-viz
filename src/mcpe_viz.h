/*
  Minecraft Pocket Edition (MCPE) World File Visualization & Reporting Tool
  (c) Plethora777, 2015.9.26

  GPL'ed code - see LICENSE

  Main classes for mcpe_viz
*/

#ifndef __MCPE_VIZ_H__
#define __MCPE_VIZ_H__

#include <map>

#include "define.h"
#include "logger.h"

namespace mcpe_viz {

  //todozooz - MAX_BLOCK_ID MAX_ITEM_ID etc

  // todo ugly globals
  extern std::string dirExec;
  //extern Logger logger;
  extern double playerPositionImageX, playerPositionImageY;
  extern int32_t playerPositionDimensionId;

  extern int32_t globalIconImageId;

  void worldPointToImagePoint(int32_t dimId, double wx, double wz, double &ix, double &iy, bool geoJsonFlag);
  void worldPointToGeoJSONPoint(int32_t dimId, double wx, double wz, double &ix, double &iy);
  
  //extern BlockInfo blockInfoList[512];

  //BlockInfo* getBlockInfo(int32_t id, int32_t blockData);
  std::string getBlockName(int32_t id, int32_t blockdata);

  int32_t getBlockByUname(const std::string& uname, int32_t& blockId, int32_t& blockData);

  //std::string getItemName(int32_t id, int32_t extraData, bool nameBasedFlag);
  
  
  class EntityInfo {
  public:
    std::string name;
    std::vector<std::string> unameList;
    std::string etype;
    
    EntityInfo(const std::string& n, const std::string& un, const std::string& e ) {
      setName(n);
      setUname(un);
      setEtype(e);
    }

    EntityInfo& setName (const std::string& s) {
      name = std::string(s);
      return *this;
    }

    EntityInfo& setUname (const std::string& s) {
      unameList = mysplit(s,';');
      return *this;
    }

    EntityInfo& setEtype (const std::string& e) {
      etype = std::string(e);
      return *this;
    }
  };

  typedef std::map<int, std::unique_ptr<EntityInfo> > EntityInfoList;
  extern EntityInfoList entityInfoList;
  bool has_key(const EntityInfoList &m, int32_t k);
  int32_t findEntityByUname(const EntityInfoList &m, std::string& un);
  //int32_t findIdByItemName(std::string& uname);
  //int32_t findIdByBlockName(std::string& uname);
  
  class BiomeInfo {
  public:
    std::string name;
    int32_t color;
    bool colorSetFlag;

    BiomeInfo(const char* n) {
      setName(n);
      setColor(kColorDefault);
      colorSetFlag = false;
    }

    BiomeInfo(const char* n, int32_t rgb) {
      setName(n);
      setColor(rgb);
    }

    BiomeInfo& setName (const std::string& s) {
      name = std::string(s);
      return *this;
    }

    BiomeInfo& setColor(int32_t rgb) {
      // note: we convert color storage to big endian so that we can memcpy when creating images
      color = htobe32(rgb);
      colorSetFlag=true;
      return *this;
    }
  };

  typedef std::map<int, std::unique_ptr<BiomeInfo> > BiomeInfoList;
  extern BiomeInfoList biomeInfoList;
  bool has_key(const BiomeInfoList &m, int32_t k);



  class EnchantmentInfo {
  public:
    std::string name;
    std::string officialName;

    EnchantmentInfo(const char* n) {
      setName(n);
      officialName="";
    }

    EnchantmentInfo& setName (const std::string& s) {
      name = std::string(s);
      return *this;
    }

    EnchantmentInfo& setOfficialName (const std::string& s) {
      officialName = std::string(s);
      return *this;
    }
  };

  typedef std::map<int, std::unique_ptr<EnchantmentInfo> > EnchantmentInfoList;
  extern EnchantmentInfoList enchantmentInfoList;
  bool has_key(const EnchantmentInfoList &m, int32_t k);

  typedef std::map<int32_t, int32_t> IntIntMap;

  extern IntIntMap mcpcToMcpeBlock;
  extern IntIntMap mcpeToMcpcBlock;
  extern IntIntMap mcpcToMcpeItem;
  extern IntIntMap mcpeToMcpcItem;

  bool has_key(const IntIntMap &m, int32_t k);

  typedef std::map<std::string, int32_t> StringIntMap;

  extern StringIntMap imageFileMap;

  bool has_key(const StringIntMap &m, const std::string& k);
  
} // namespace mcpe_viz

#endif // __MCPE_VIZ_H__
