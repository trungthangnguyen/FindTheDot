//
//  MyScrollLayer.h
//
//
//  Created by Hieu Nguyen Trung on 5/19/14.
//
//

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MyScrollLayer;

class MyScrollLayerDelegate {
public:
    virtual void myScrollLayer_actionWhenActiveChange(MyScrollLayer *scroller) = 0; // khi active panel thay đổi
    virtual void myScrollLayer_actionWhenTouchMoving(MyScrollLayer *scroller) = 0; // khi tay người chơi move
    virtual void myScrollLayer_actionWhenBouncing(MyScrollLayer *scroller) = 0; // khi panel bật lại hoặc chạy sang panel mới
    virtual void myScrollLayer_actionWhenBouncingBegan(MyScrollLayer *scroller, float duration) = 0; // khi panel bắt đầu bật lại
};

class MyScrollLayer : public Node {
protected:
    MyScrollLayerDelegate   *_delegate;     // assign var
    Touch                   *_usedTouch;    // assign var
    Node                    *_container;    // child
    Node                    *_pagination;   // child
    Action                  *_moveAction;   // retain var
    
    int                     _numbOfPanel;           // số lượng panel
    int                     _activePanel;           // tính từ 1 trở đi
    float                   _panelWidth;            // chiều rộng của một panel, mặc định bằng chiều rộng màn hình
    float                   _marginWidth;
    float                   _returnSpeed;           // tốc độ bật/move của panel, đơn vị là pixel/giây
    float                   _touchTime;             // thời gian touch
    bool                    _lockTouch;
    bool                    _roundEnabled;          // cho phép quay vòng các panel hay không
    bool                    _isTouchCaptured;       // cho biết touch có tạo ra move hay không hoặc có đang move hay không
    bool                    _touchEnabled;          // cho phép touch hay không
    bool                    _panelColorsEnabled;    // bật tắt chế độ màu cho từng panel, mặc định là false
    cocos2d::Point          _oldTouchPoint;
    Color3B                 _paginationDefaultColor;
    Color3B                 _paginationActiveColor;
    std::vector<Color3B>    _panelColors;           // màu của từng panel: phần tử 0 -> panel 1, phần tử 1 -> panel 2
    
    bool init();
    
    void update(float dt);
    void unscheduleUpdate();
    void updateTouchTime(float dt);
    void scheduleUpdateTouchTime();
    void unscheduleUpdateTouchTime();
    
    void changeActiveEnded();
    void resetPanels();
    void setAfterLast();
    void setBeforeFirst();
    void setMoveAction(Action *action);
    float positionXByActivePanel();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    
    virtual void createPagination();
    virtual void updatePagination();
    
public:
    CREATE_FUNC(MyScrollLayer);
    
    int getActivePanel() {return _activePanel;};
    float getPanelWidth() {return _panelWidth;};
    float getMarginWidth() {return _marginWidth;};
    float getReturnSpeed() {return _returnSpeed;};
    bool isRoundEnabled() {return _roundEnabled;};
    bool isTouchCaptured() {return _isTouchCaptured;};
    bool isTouchEnabled() {return _touchEnabled;};
    Color3B getPaginationDefaultColor() {return _paginationDefaultColor;};
    Color3B getPaginationActiveColor() {return _paginationActiveColor;};
    Node * getPagination() {return _pagination;};
    
    void setMarginWidth(float marginWidth) {_marginWidth = marginWidth;};
    void setReturnSpeed(float returnSpeed) {_returnSpeed = returnSpeed;};
    void setRoundEnabled(bool roundEnabled) {_roundEnabled = roundEnabled;};
    void setDelegate(MyScrollLayerDelegate *delegate) {_delegate = delegate;};
    
    // ...
    void setPanelColorsEnabled(bool enabled, std::vector<Color3B> colors);
    void setTouchEnabled(bool enabled); // sao chép từ class Layer, nếu cocos thay đổi gì thì lại copy phần touchEnabled từ CCLayer thôi
    void setActivePanel(int activePanel);
    void setPanelWidth(float panelWidth);
    
    void addChildPanel(Node *node);
    void removeChildPanel(Node *node);
    void removeChildPanelByTag(int tag);
    void resetTouchHandle(); // có thể gọi khi applicationWillResignActive
    
    void setPaginationActiveColor(Color3B color);
    void setPaginationDefaultColor(Color3B color);
    
    /*
     *  gọi hàm này khi kích thước màn hình bị thay đổi, đấy là trong trường hợp panelWidth fix theo chiều rộng màn hình
     *  còn trong trường hợp panelWidth fix cứng thì phải thêm biến panelWidthFixed -> viết thêm code vào
     */
    virtual void actionWhenScreenSizeChanged();
};
