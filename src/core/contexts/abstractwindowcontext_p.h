#ifndef ABSTRACTWINDOWCONTEXT_P_H
#define ABSTRACTWINDOWCONTEXT_P_H

#include <QtCore/QSet>
#include <QtGui/QWindow>
#include <QtGui/QPolygon>

#include <QWKCore/corewindowagent.h>
#include <QWKCore/windowitemdelegate.h>

namespace QWK {

    class QWK_CORE_EXPORT AbstractWindowContext : public QObject {
        Q_OBJECT
    public:
        inline AbstractWindowContext(QWindow *window, WindowItemDelegate *delegate)
            : m_windowHandle(window), m_delegate(delegate) {
        }
        ~AbstractWindowContext();

    public:
        virtual bool setup() = 0;

        inline QWindow *window() const;
        void setupWindow(QWindow *window);

        inline bool isHitTestVisible(QObject *obj) const;
        bool setHitTestVisible(QObject *obj, bool visible);
        bool setHitTestVisible(const QRect &rect, bool visible);

        inline QObject *systemButton(CoreWindowAgent::SystemButton button) const;
        bool setSystemButton(CoreWindowAgent::SystemButton button, QObject *obj);

        inline QObject *titleBar() const;
        bool setTitleBar(QObject *obj);

        void showSystemMenu(const QPoint &pos);

    protected:
        QWindow *m_windowHandle;
        WindowItemDelegate *m_delegate;

        QSet<QObject *> m_hitTestVisibleItems;
        QList<QRect> m_hitTestVisibleRects;

        QObject *m_titleBar{};
        QObject *m_systemButtons[CoreWindowAgent::NumSystemButton]{};

        mutable bool hitTestVisibleShapeDirty{};
        mutable QPolygon hitTestVisibleShape;
    };

    inline QWindow *AbstractWindowContext::window() const {
        return m_windowHandle;
    }

    inline bool AbstractWindowContext::isHitTestVisible(QObject *obj) const {
        return m_hitTestVisibleItems.contains(obj);
    }

    inline QObject *
        AbstractWindowContext::systemButton(CoreWindowAgent::SystemButton button) const {
        return m_systemButtons[button];
    }

    inline QObject *AbstractWindowContext::titleBar() const {
        return m_titleBar;
    }

}

#endif // ABSTRACTWINDOWCONTEXT_P_H