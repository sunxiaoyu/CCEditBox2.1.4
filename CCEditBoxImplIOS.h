/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCEditBoxIMPLIOS_H__
#define __CCEditBoxIMPLIOS_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCEditBoxImpl.h"

NS_CC_EXT_BEGIN

class CCEditBox;

class CCEditBoxImplIOS : public CCEditBoxImpl
{
public:
    CCEditBoxImplIOS(CCEditBox* pEditText);
    virtual ~CCEditBoxImplIOS();
    
    virtual bool initWithSize(const CCSize& size);
    virtual void setFontColor(const ccColor3B& color);
    virtual void setPlaceholderFontColor(const ccColor3B& color);
    virtual void setInputMode(EditBoxInputMode inputMode);
    virtual void setInputFlag(EditBoxInputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    virtual void setReturnType(KeyboardReturnType returnType);
    virtual bool isEditing();
    
    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void setPlaceHolder(const char* pText);
    virtual void setText1(const char* pText);
    virtual const char* getText1(void);
    virtual void setPlaceHolder1(const char* pText);
    virtual void setPosition(const CCPoint& pos);
    virtual void setContentSize(const CCSize& size);
    virtual void visit(void);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    
    virtual void addTextfield();
    virtual void removeTextfield();
    virtual void openKeyboard();
    virtual void closeKeyboard();

    
private:
    CCSize     m_tContentSize;
    void*      m_pSysEdit;
    int        m_nMaxTextLength;
    bool       m_bInRetinaMode;
    
    CCPoint    m_obPosition;
    CCPoint    m_obAnchorPoint;
};


NS_CC_EXT_END

#endif /* __CCEditBoxIMPLIOS_H__ */

