//
//  rc_object.hpp
//  c++_code
//
//  Created by 林叉叉 on 2018/5/31.
//  Copyright © 2018年 林叉叉. All rights reserved.
//

#ifndef RC_OBJECT_H
#define RC_OBJECT_H

#include "config.h"

FL_ENTER

class RCObject
{
public:
    RCObject();
    virtual ~RCObject();
    
    RCObject(const RCObject& rhs);
    RCObject& operator=(const RCObject& rhs);
    
    void IncreaseRef();
    void DecreaseRef();
    
    size_t CountRef() const;
    bool IsNoRef() const;
    
    void MarkUnshareable();
    bool IsShareable() const;
    
    bool IsShared() const;
    
private:
    size_t reference_count;
    bool shareable;
};


FL_LEAVE

#endif /* rc_object_hpp */
