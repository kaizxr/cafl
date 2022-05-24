#pragma once

class TextListener
{
public:
    TextListener(){};
    ~TextListener(){};
    virtual void onTextChanged(int code) = 0;
};