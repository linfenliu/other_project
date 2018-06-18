//
//  test_smart_ptr.cpp
//  c++_code
//
//  Created by 林叉叉 on 2018/5/31.
//  Copyright © 2018年 林叉叉. All rights reserved.
//



#include "smart_ptr.h"
#include "rc_object.h"


FL_ENTER

class TestRCObject:public RCObject
{
public:
    TestRCObject():value(5){}
    
    int value;
};


void TestSmartPtr()
{
    TestRCObject test;
    
    {
        SmartPtr<TestRCObject> ptr(new TestRCObject);
        auto ptr0 = ptr;
        auto ptr1 = ptr0;

        auto xxx = *ptr0;
        auto yyy = *ptr1;
        
    }
    
    {
        SmartPtr<TestRCObject> ptr(new TestRCObject);
        auto ptr0(ptr);
        
        auto ptr1(ptr0);
    }
    
    SmartPtr<TestRCObject> ptr(new TestRCObject);
}

FL_LEAVE


