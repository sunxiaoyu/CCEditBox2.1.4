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

#include "CCEditBox.h"
#include "CCEditBoxImpl.h"

NS_CC_EXT_BEGIN

CCEditBox::CCEditBox(void)
: m_pEditBoxImpl(NULL)
, m_pDelegate(NULL)
, m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
, m_eEditBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
, m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
, m_colText(ccBLACK)
, m_textLabel(NULL)
, m_colPlaceHolder(ccGRAY)
, m_textHolderLabel(NULL)
, m_nMaxLength(0)
, m_fAdjustHeight(0.0f)
{
}

CCEditBox::~CCEditBox(void)
{
    CC_SAFE_DELETE(m_pEditBoxImpl);
}


void CCEditBox::touchDownAction(CCObject *sender, CCControlEvent controlEvent)
{    
    m_pEditBoxImpl->openKeyboard();
}

CCEditBox* CCEditBox::create(const CCSize& size, CCScale9Sprite* pNormal9SpriteBg, CCScale9Sprite* pPressed9SpriteBg/* = NULL*/, CCScale9Sprite* pDisabled9SpriteBg/* = NULL*/)
{
    CCEditBox* pRet = new CCEditBox();
    
    if (pRet != NULL && pRet->initWithSizeAndBackgroundSprite(size, pNormal9SpriteBg))
    {
        if (pPressed9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pPressed9SpriteBg, CCControlStateHighlighted);
        }
        
        if (pDisabled9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pDisabled9SpriteBg, CCControlStateDisabled);
        }
    
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool CCEditBox::initWithSizeAndBackgroundSprite(const CCSize& size, CCScale9Sprite* pPressed9SpriteBg)
{
    if (CCControlButton::initWithBackgroundSprite(pPressed9SpriteBg))
    {
        m_pEditBoxImpl = __createSystemEditBox(this);
        m_pEditBoxImpl->initWithSize(size);
        
        this->setPreferredSize(size);
        this->setPosition(ccp(0, 0));
        this->setZoomOnTouchDown(false);
        this->addTargetWithActionForControlEvent(this, cccontrol_selector(CCEditBox::touchDownAction), CCControlEventTouchUpInside);
        
        m_textHolderLabel = CCLabelTTF::create("", "TrebuchetMS", size.height*2/3);
        m_textHolderLabel->setAnchorPoint(ccp(0.0f, 0.5f));
        m_textHolderLabel->setPosition(ccp(2.0f, size.height * 0.5f));
        m_textHolderLabel->setColor(m_colPlaceHolder);
        addChild(m_textHolderLabel, 255);
        
        m_textLabel = CCLabelTTF::create("", "TrebuchetMS", size.height*2/3);
        m_textLabel->setAnchorPoint(ccp(0.0f, 0.5f));
        m_textLabel->setPosition(ccp(2.0f, size.height * 0.5f));
        m_textLabel->setColor(m_colText);
        addChild(m_textLabel, 255);
        
        return true;
    }
    return false;
}

void CCEditBox::setDelegate(CCEditBoxDelegate* pDelegate)
{
    m_pDelegate = pDelegate;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setDelegate(pDelegate);
    }
}

void CCEditBox::setText(const char* pText)
{
    if (pText != NULL)
    {
        m_strText = pText;
        if (m_textLabel != NULL)
        {
            m_textLabel->setString(pText);
            if (strlen(m_strText.c_str()) != 0)
            {
                m_textHolderLabel->setString("");
                if (m_eEditBoxInputFlag == kEditBoxInputFlagPassword)
                {
                    CCString *_cc_string = CCString::create("");
                    for (int i=0; i<strlen(pText); ++i) {
                        _cc_string = CCString::createWithFormat("%s%s", _cc_string->getCString(), "●");
                    }
                    m_textLabel->setString(_cc_string->getCString());
                }
            }
        }
    }
}

const char* CCEditBox::getText(void)
{
    return m_strText.c_str();;
}

void CCEditBox::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    if (m_textLabel != NULL)
    {
        m_textLabel->setColor(color);
    }
}

void CCEditBox::setPlaceholderFontColor(const ccColor3B& color)
{
    m_colPlaceHolder = color;
    if (m_textHolderLabel != NULL)
    {
        m_textHolderLabel->setColor(color);
    }
}

void CCEditBox::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        m_strPlaceHolder = pText;
        if (m_textHolderLabel != NULL)
        {
            if (strlen(m_strText.c_str()) == 0)
            {
                m_textHolderLabel->setString(pText);
            }
        }
    }
}

const char* CCEditBox::getPlaceHolder(void)
{
    return m_strPlaceHolder.c_str();
}

void CCEditBox::setInputMode(EditBoxInputMode inputMode)
{
    m_eEditBoxInputMode = inputMode;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setInputMode(inputMode);
    }
}

void CCEditBox::setMaxLength(int maxLength)
{
    m_nMaxLength = maxLength;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setMaxLength(maxLength);
    }
}


int CCEditBox::getMaxLength()
{
    return m_nMaxLength;
}

void CCEditBox::setInputFlag(EditBoxInputFlag inputFlag)
{
    m_eEditBoxInputFlag = inputFlag;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setInputFlag(inputFlag);
    }
}

void CCEditBox::setReturnType(KeyboardReturnType returnType)
{
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setReturnType(returnType);
    }
}

/* override function */
void CCEditBox::setPosition(const CCPoint& pos)
{
    CCControlButton::setPosition(pos);
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setPosition(pos);
    }
}

void CCEditBox::setContentSize(const CCSize& size)
{
    CCControlButton::setContentSize(size);
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setContentSize(size);
    }
}

void CCEditBox::visit(void)
{
    CCControlButton::visit();
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->visit();
    }
}

void CCEditBox::onEnter(void)
{
    CCControlButton::onEnter();
    if (m_pEditBoxImpl != NULL)
    {
        // add system edit control
        m_pEditBoxImpl->addTextfield();
    }
}

void CCEditBox::onExit(void)
{
    CCControlButton::onExit();
    if (m_pEditBoxImpl != NULL)
    {
        // remove system edit control
        m_pEditBoxImpl->removeTextfield();
    }
}

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

void CCEditBox::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillShow");
    CCRect rectTracked = getRect(this);
    
    //postion bug fix code -sunxy
    if (m_pParent != NULL)
    {
        rectTracked.origin = m_pParent->convertToWorldSpace(rectTracked.origin);
    }
    
    // if the keyboard area doesn't intersect with the tracking node area, nothing needs to be done.
    if (!rectTracked.intersectsRect(info.end))
    {
        CCLOG("needn't to adjust view layout.");
        return;
    }
    
    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    m_fAdjustHeight = info.end.getMaxY() - rectTracked.getMinY();
    // CCLOG("CCEditBox:needAdjustVerticalPosition(%f)", m_fAdjustHeight);
    
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->doAnimationWhenKeyboardMove(info.duration, m_fAdjustHeight);
    }
}

void CCEditBox::keyboardDidShow(CCIMEKeyboardNotificationInfo& info)
{

}

void CCEditBox::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillHide");
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->doAnimationWhenKeyboardMove(info.duration, -m_fAdjustHeight);
    }
}

void CCEditBox::keyboardDidHide(CCIMEKeyboardNotificationInfo& info)
{

}


NS_CC_EXT_END
