#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

// ---------------------------
// Detect portals
// ---------------------------
bool isAnyPortal(int id) {
    return
        id == 12   || // Cube
        id == 13   || // Ship
        id == 47   || // Ball
        id == 111  || // UFO
        id == 660  || // Wave
        id == 745  || // Robot
        id == 1331 || // Spider
        id == 3006 || // Swing
        id == 10   || id == 11 || // Gravity
        id == 45   || id == 46 || // Dual
        id == 99   || id == 100;  // Mirror
}

// ---------------------------
// Main hook
// ---------------------------
class $modify(ClassicPortals, GameObject) {
public:
    void customSetup() {
        GameObject::customSetup();

        if (!isAnyPortal(this->m_objectID)) return;

        // ✅ Use member pointer for schedule
        this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&ClassicPortals::hideSprites), 0.01f);
    }

    // ---------------------------
    // Member function to hide sprites
    void hideSprites(float) {
        CCObject* obj;
        CCARRAY_FOREACH(this->getChildren(), obj) {
            auto node = static_cast<CCNode*>(obj);
            auto sprite = typeinfo_cast<CCSprite*>(node);
            if (!sprite) continue;

            auto s = sprite->getContentSize();

            bool verySmall = s.width < 55 && s.height < 55;   // icons
            bool veryBig   = s.width > 125 || s.height > 125; // modern circles
            bool glowLike  = s.width > 90 && s.width < 110;   // new glow

            if (verySmall || veryBig || glowLike) {
                sprite->setOpacity(0);
            }
        }
    }
};

// ---------------------------
$on_mod(Loaded) {
    log::info("Classic Portals loaded (classic mode active).");
}
