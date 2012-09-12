//
//  WordDictionary.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/23/12.
//
//

#ifndef WordChallenge_WordDictionary_h
#define WordChallenge_WordDictionary_h

#include "cocos2d.h"
#include <sqlite3.h>
#include <string>



using namespace cocos2d;

class WordDictionary;

static WordDictionary* g_sWordDictionary = NULL;

class WordDictionary : public CCObject
{
protected:
    
    sqlite3* m_db;
    
    WordDictionary()
    {
        const char* path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("dictionary.db");
        if (sqlite3_open(path,&m_db) )
        {
            CCLog("Can't open Word Database %s - %s",path,sqlite3_errmsg(m_db));
            sqlite3_close(m_db);
            m_db = NULL;
        }
        
        
    }
    
    
    
    
public:
    
    static WordDictionary* instance()
    {
        if (g_sWordDictionary == NULL)
        {
            g_sWordDictionary = new WordDictionary();
        }
        return g_sWordDictionary;
    }
    
    
    
    
    ~WordDictionary()
    {
        if ( m_db != NULL)
        {
            sqlite3_close(m_db);
        }
    }
    
    
    bool wordCorrect(std::string word)
    {
        const char * query = "select * from words where word = lower(?)";
        sqlite3_stmt *sqlStatement;
        if(sqlite3_prepare_v2(m_db, query, -1, &sqlStatement, NULL) != SQLITE_OK)
        {
            CCLog("Problem with prepare statement %s",query);
            return false;
        }
        
        sqlite3_bind_text(sqlStatement, 1, word.c_str(), -1, SQLITE_TRANSIENT);
        
        
        bool found = false;
        int ret = sqlite3_step(sqlStatement);
        if(ret == SQLITE_ROW)
        {
            found = true;
        }

        sqlite3_finalize(sqlStatement);
        return found;
    }
};


#endif
