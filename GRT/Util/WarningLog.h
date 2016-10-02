/*
GRT MIT License
Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef GRT_WARNING_LOG_HEADER
#define GRT_WARNING_LOG_HEADER

#include "Log.h"
#include "ObserverManager.h"

GRT_BEGIN_NAMESPACE
    
class GRT_API WarningLogMessage{
public:
    WarningLogMessage(std::string key = "",std::string message = ""){
        this->key = key;
        this->message = message;
    }
    ~WarningLogMessage(){
        
    }
    
    std::string getProceedingText() const {
        return key;
    }
    
    std::string getMessage() const {
        return message;
    }
    
    std::string key;
    std::string message;
};

class GRT_API WarningLog : public GRT::Log{
public:
    WarningLog(const std::string &key = "" ) : Log( key )
    {
        Log::loggingEnabledPtr = &warningLoggingEnabled;
    }

    virtual ~WarningLog(){}

    WarningLog& operator=(const WarningLog &rhs){
        if( this != &rhs ){
            this->loggingEnabledPtr = &warningLoggingEnabled;
        }
        return *this;
    }
    
    //Getters
    virtual bool loggingEnabled() const{ return warningLoggingEnabled; }
    
    //Setters
    static bool enableLogging(bool loggingEnabled);
    
    static bool registerObserver(Observer< WarningLogMessage > &observer);
    
    static bool removeObserver(Observer< WarningLogMessage > &observer);

protected:
    virtual void triggerCallback( const std::string &message ) const{
        observerManager.notifyObservers( WarningLogMessage(key,message) );
        return;
    }
    
    static ObserverManager< WarningLogMessage > observerManager;
    static bool warningLoggingEnabled;
};

GRT_END_NAMESPACE

#endif //GRT_WARNING_LOG_HEADER
