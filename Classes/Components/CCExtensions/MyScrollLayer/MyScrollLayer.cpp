//
//  MyScrollLayer.cpp
//
//
//  Created by Hieu Nguyen Trung on 5/19/14.
//
//

#include "MyScrollLayer.h"
#include "../../ScreenSettings/ScreenSettings.h"

#define DISTANCE_FOR_TOUCH_CAPTURE  4.0f
#define DISTANCE_FOR_CHANGE_LAYER   32.0f   /* dung ket hop voi DURATION_FOR_CHANGE_LAYER */
#define DURATION_FOR_CHANGE_LAYER   0.2f    /* dung ket hop voi DISTANCE_FOR_CHANGE_LAYER */

#pragma mark Initialize
bool MyScrollLayer::init(){
    if (Node::init()) {
//        Size visibleSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize(); // nếu không dùng ScreenSettings
        Size visibleSize = SS_DESIGN_SIZE;
        
        _numbOfPanel = 0;
        _activePanel = 1;
        _panelWidth = visibleSize.width;
        _marginWidth = 32.0f;
        _returnSpeed = visibleSize.width*3.0f;
        _lockTouch = false;
        _roundEnabled = true;
        _isTouchCaptured = false;
        _paginationDefaultColor = Color3B::YELLOW;
        _paginationActiveColor = Color3B::RED;
        
        _container = Node::create();
        _container->setPosition(Point(0, 0));
        this->addChild(_container);
        
        _pagination = Node::create();
        _pagination->setPosition(Point(0, 0));
        this->addChild(_pagination);
        
        this->setTouchEnabled(true);
        
        return true;
    }
    
    return false;
}

#pragma mark handle with properties
void MyScrollLayer::setPanelColorsEnabled(bool enabled, std::vector<Color3B> colors){
    _panelColorsEnabled = enabled;
    
    if (_panelColorsEnabled && !colors.empty()) {
        _panelColors = colors;
        _paginationActiveColor = colors.at(_activePanel - 1);
        this->updatePagination();
    }
}

void MyScrollLayer::setTouchEnabled(bool enabled){
    if (_touchEnabled != enabled) {
        _touchEnabled = enabled;
        
        if (enabled) {
            // Register Touch Event
            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            
            listener->onTouchBegan = CC_CALLBACK_2(MyScrollLayer::onTouchBegan, this);
            listener->onTouchMoved = CC_CALLBACK_2(MyScrollLayer::onTouchMoved, this);
            listener->onTouchEnded = CC_CALLBACK_2(MyScrollLayer::onTouchEnded, this);
            listener->onTouchCancelled = CC_CALLBACK_2(MyScrollLayer::onTouchCancelled, this);
            
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
            
        } else {
            _eventDispatcher->removeEventListenersForTarget(this);
        }
    }
}

void MyScrollLayer::setMoveAction(Action *action) {
    if (_moveAction) {
        _moveAction->release();
    }
    
    if (action) {
        action->retain();
    }
    
    _moveAction = action;
}

void MyScrollLayer::setActivePanel(int active_){
    _activePanel = active_;
    
    if (_numbOfPanel >= 3) {
        if (_activePanel == 1) {
            this->setBeforeFirst();
        } else if (_activePanel == _numbOfPanel) {
            this->setAfterLast();
        } else {
            _container->getChildByTag(1)->setPosition(Point(0, 0));
            _container->getChildByTag(_numbOfPanel)->setPosition(Point(_panelWidth*(_numbOfPanel - 1), 0));
        }
    }
    
    _container->setPosition(Point(this->positionXByActivePanel(), 0));
    this->updatePagination();
    
    if (_delegate) {
        _delegate->myScrollLayer_actionWhenActiveChange(this);
    }
}

void MyScrollLayer::setPanelWidth(float panelWidth){
    // code me here
}

void MyScrollLayer::addChildPanel(Node *node){
    _numbOfPanel++;
    
    node->setTag(_numbOfPanel);
    node->setPosition(Point(_panelWidth*(_numbOfPanel - 1), 0));
    _container->addChild(node);
    
    this->setContentSize(Size(_panelWidth*_numbOfPanel, MAX(this->getContentSize().height, node->getContentSize().height)));
    this->createPagination();
}

void MyScrollLayer::removeChildPanel(Node *node){
    // code me here
}

void MyScrollLayer::removeChildPanelByTag(int tag){
    // code me here
}

#pragma mark Pagination
void MyScrollLayer::createPagination(){
    _pagination->setPosition(Point(SS_DESIGN_WIDTH/2, 128*SS_SCALE_FACTOR));
    _pagination->removeAllChildrenWithCleanup(true);
    
    float paddingX = 48;
    float startX = paddingX*(1 - _numbOfPanel)/2;
    
    for (int i=1; i<=_numbOfPanel; i++) {
        auto p = LayerColor::create(Color4B::BLACK, 24, 24);
        p->setTag(i); // tag này phải trùng tag của panel mà nó đại diện
        p->setPosition(Point(startX + paddingX*(i-1), 0) - p->getContentSize()/2);
        p->setColor(_activePanel == i ? _paginationActiveColor : _paginationDefaultColor);
        _pagination->addChild(p);
    }
}

void MyScrollLayer::updatePagination(){
    int num = (int)_pagination->getChildren().size();
    
    for (int i=0; i<num; i++) {
        LayerColor *p = (LayerColor *)_pagination->getChildren().at(i);
        
        if (p->getTag() == _activePanel) {
            p->setColor(_paginationActiveColor);
        } else {
            p->setColor(_paginationDefaultColor);
        }
    }
}

void MyScrollLayer::setPaginationActiveColor(Color3B color){
    _paginationActiveColor = color;
    this->updatePagination();
}

void MyScrollLayer::setPaginationDefaultColor(Color3B color){
    _paginationDefaultColor = color;
    this->updatePagination();
}

#pragma mark actionWhenScreenSizeChanged
void MyScrollLayer::actionWhenScreenSizeChanged(){
    _panelWidth = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
    
    this->resetPanels();
}

#pragma mark update
void MyScrollLayer::update(float dt){
    if (_moveAction && !_moveAction->isDone()) {
        _moveAction->step(dt);
        
        if (_delegate) {
            _delegate->myScrollLayer_actionWhenBouncing(this);
        }
        
    } else {
        this->unscheduleUpdate();
    }
}

void MyScrollLayer::unscheduleUpdate(){
    Node::unscheduleUpdate();
    this->setMoveAction(nullptr);
}

void MyScrollLayer::scheduleUpdateTouchTime(){
    _touchTime = 0;
    this->schedule(schedule_selector(MyScrollLayer::updateTouchTime));
}

void MyScrollLayer::unscheduleUpdateTouchTime(){
    this->unschedule(schedule_selector(MyScrollLayer::updateTouchTime));
}

void MyScrollLayer::updateTouchTime(float dt){
    _touchTime += dt;
}

#pragma mark Utilities
void MyScrollLayer::changeActiveEnded(){
    this->resetPanels();
}

void MyScrollLayer::resetTouchHandle(){
    _lockTouch = false;
    _isTouchCaptured = false;
    _usedTouch = nullptr;
    
    this->setActivePanel(_activePanel);
}

void MyScrollLayer::resetPanels(){
    for (int i=1; i<=_numbOfPanel; i++) {
        _container->getChildByTag(i)->setPosition(Point(_panelWidth*(i - 1), 0));
    }
    
    this->resetTouchHandle();
}

void MyScrollLayer::setAfterLast(){
    _container->getChildByTag(1)->setPosition(Point(_panelWidth*_numbOfPanel, 0));
}

void MyScrollLayer::setBeforeFirst(){
    _container->getChildByTag(_numbOfPanel)->setPosition(Point(-_panelWidth, 0));
}

float MyScrollLayer::positionXByActivePanel(){
    return -_panelWidth*(_activePanel - 1);
}

#pragma mark EventListenerTouchOneByOne
bool MyScrollLayer::onTouchBegan(Touch* touch, Event* event){
    if (_lockTouch || (_usedTouch != nullptr && _usedTouch != touch)) {
        return false;
    }
    
    _usedTouch = touch;
    _oldTouchPoint = touch->getLocation();
    
    this->scheduleUpdateTouchTime();
    
    return true;
}

void MyScrollLayer::onTouchMoved(Touch* touch, Event* event){
    if (_lockTouch || _usedTouch != touch) {
        return;
    }
    
    Point newPos = touch->getLocation();
    float posX = _container->getPosition().x + newPos.x - _oldTouchPoint.x;
    _container->setPosition(Point(posX, _container->getPosition().y));
    _oldTouchPoint = newPos;
    
    if (_isTouchCaptured == false) {
        float activePosX = this->positionXByActivePanel();
        float diff = _container->getPosition().x - activePosX;
        
        if (fabsf(diff) > DISTANCE_FOR_TOUCH_CAPTURE) {
            _isTouchCaptured = true;
        }
    }
}

void MyScrollLayer::onTouchEnded(Touch* touch, Event* event){
    if (_lockTouch || _usedTouch != touch) {
        return;
    }
    
    _lockTouch = true;
    _usedTouch = nullptr;
    
    float activePosX = this->positionXByActivePanel();
    float diff = _container->getPosition().x - activePosX;
    float limit;
    int curActive = _activePanel;
    
    if (_touchTime < DURATION_FOR_CHANGE_LAYER) {
        limit = DISTANCE_FOR_CHANGE_LAYER;
    } else {
        limit = _panelWidth/2 - _marginWidth;
    }
    
    if (diff > 0 && diff > limit && ((_roundEnabled == false && curActive > 1) || _roundEnabled)) {         // di chuyen tu trai -> phai
        int active = _activePanel - 1;
        
        if (active == 0) {
            active = _numbOfPanel;
        }
        
        _activePanel = active;
        
        if (active == _numbOfPanel) {
            activePosX = _panelWidth;
        } else {
            activePosX = this->positionXByActivePanel();
        }
    }
    else if (diff < 0 && -diff > limit && ((_roundEnabled == false && curActive > 1) || _roundEnabled)) {   // di chuyen tu phai -> trai
        int active = _activePanel + 1;
        
        if (active > _numbOfPanel) {
            active = 1;
        }
        
        _activePanel = active;
        
        if (active == 1) {
            activePosX = -_panelWidth*_numbOfPanel;
        } else {
            activePosX = this->positionXByActivePanel();
        }
    }
    
    if (_isTouchCaptured == false && fabsf(diff) > DISTANCE_FOR_TOUCH_CAPTURE) {
        _isTouchCaptured = true;
    }
    
    if (curActive != _activePanel) {    // activePanel thay doi
        _isTouchCaptured = true;
    }
    
    float duration = fabsf(_container->getPosition().x - activePosX)/_returnSpeed;
    
    Action *action = Sequence::create(EaseBackOut::create(MoveTo::create(duration, Point(activePosX, _container->getPosition().y))), CallFunc::create(CC_CALLBACK_0(MyScrollLayer::changeActiveEnded, this)), NULL);
    this->setMoveAction(action);
    _moveAction->startWithTarget(_container);
    
    if (_panelColorsEnabled && curActive != _activePanel) { // activePanel thay doi va bat che do panelColor
        _paginationActiveColor = _panelColors.at(_activePanel-1);
        _pagination->getChildByTag(curActive)->runAction(TintTo::create(duration, _paginationDefaultColor));
        _pagination->getChildByTag(_activePanel)->runAction(TintTo::create(duration, _paginationActiveColor));
    }
    
    if (_delegate) {
        _delegate->myScrollLayer_actionWhenBouncingBegan(this, duration);
    }
    
    this->scheduleUpdate();
    this->unscheduleUpdateTouchTime();
}

void MyScrollLayer::onTouchCancelled(Touch* touch, Event* event){
    this->resetTouchHandle();
}
