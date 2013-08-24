//
//  ProtoDatabase.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef WordChallenge_ProtoDatabase_h
#define WordChallenge_ProtoDatabase_h


#include "cocos2d.h"
#include "json/json.h"
#include <fstream>
#include "PlatformHelper.h"
using namespace cocos2d;



class ProtoDatabase;

static ProtoDatabase* s_sharedProtodatabase;


class ProtoDatabase : CCObject
{
protected:
    
    Json::Value m_letersProtoData;
    Json::Value m_boardProtoData;
    
    ProtoDatabase()
    {
        m_letersProtoData = this->loadFile("letters")["letters"];

    }
    
    
public:
    
    static ProtoDatabase* shardInstance()
    {
        if (s_sharedProtodatabase == NULL)
        {
            s_sharedProtodatabase = new ProtoDatabase();
        }
        return s_sharedProtodatabase;
    }
    
    
    ~ProtoDatabase()
    {
        
    }
    
    Json::Value loadFile(std::string file)
    {
        Json::Value root;
        Json::Reader reader;
        
        
        bool parsingSuccessful = reader.parse(getJsonFileContents(file), root );
        if ( !parsingSuccessful ) 
        {
            CCLog("Failed to Parse Protodata file %s",file.c_str());
            return NULL;
        }
        return root;
        
    }
    
    Json::Value getLetterProtoDataById(int id_)
    {
        return m_letersProtoData[id_];
    }
    
    int getLettersProtoDataSize()
    {
        return m_letersProtoData.size();
    }
    
    Json::Value getBoardProtoData()
    {
        return m_boardProtoData;
    }
};



#endif
