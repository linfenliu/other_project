//
//  rc_object.cpp
//  c++_code
//
//  Created by 林叉叉 on 2018/5/31.
//  Copyright © 2018年 林叉叉. All rights reserved.
//

#include "rc_object.h"

FL_ENTER

RCObject::RCObject()
    :reference_count(0),shareable(true)
{}


RCObject::~RCObject()
{}


RCObject::RCObject(const RCObject& rhs)
    :reference_count(0),shareable(true)
{}


RCObject& RCObject::operator=(const RCObject& rhs)
{
    return *this;
}


void RCObject::IncreaseRef()
{
    ++reference_count;
}


void RCObject::DecreaseRef()
{
    if(--reference_count == 0) delete this;
}


size_t RCObject::CountRef() const
{
    return reference_count;
}

bool RCObject::IsNoRef() const
{
    return reference_count == 0;
}


void RCObject::MarkUnshareable()
{
    shareable = false;
}


bool RCObject::IsShareable() const
{
    return shareable;
}


bool RCObject::IsShared() const
{
    return reference_count > 1;
}

FL_LEAVE
