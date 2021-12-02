#pragma once
#include <gtest/gtest.h>
#include <QTest>
#include <QPoint>
#include <QScreen>
#include "../../src/screenshot.h"
#include "../../src/utils.h"
#include "../../src/main_window.h"
#include "stub.h"
#include "addr_pri.h"


using namespace testing;
//ACCESS_PRIVATE_FIELD(Screenshot, MainWindow*, m_window);
static int state = 0;

QRect geometry_stub_()
{
    return QRect(0, 0, 1920, 1080);
}

void passInputEvent_stub_(int wid)
{
    Q_UNUSED(wid);
}

qreal devicePixelRatio_stub_1()
{
    return 1;
}

int width_stub()
{
    return 1920;
}

int height_stub()
{
    return 1080;
}

QVariant getShotCfg_stub(void *obj, const QString &group, const QString &key)
{
    if (group == "save") {
        if (key == "format") {
            return state % 3;
        } else if (key == "save_op") {
            return (state + 1) % 3; // 0 desktop 1 image 2autoSave 3 SaveToSpecificDir
        }
    }
    return true;
}

class ScreenshotTest: public testing::Test
{

public:
    Screenshot *shot = new Screenshot;
    MainWindow *mwindow;
    QEventLoop loop;
    Stub stub;
    virtual void SetUp() override
    {
        qDebug() << "++++++" << __FUNCTION__ << __LINE__;
    }

    virtual void TearDown() override
    {
        stub.reset(ADDR(ConfigSettings, value));
        qDebug() << "++++++" << __FUNCTION__ << __LINE__;
    }
};

void initAttributes_stub1()
{

}
void initResource_stub1()
{

}
void initLaunchMode_stub1(QString launchMode)
{

}
void showFullScreen_stub1()
{

}
void initPadShot_stub()
{

}
ACCESS_PRIVATE_FIELD(Screenshot, MainWindow, m_window);
TEST_F(ScreenshotTest, startScreenshot)
{
    stub.set(ADDR(MainWindow, initAttributes), initAttributes_stub1);
    stub.set(ADDR(MainWindow, initResource), initResource_stub1);
    stub.set(ADDR(MainWindow, initLaunchMode), initLaunchMode_stub1);
    stub.set(ADDR(MainWindow, showFullScreen), showFullScreen_stub1);
    stub.set(ADDR(MainWindow, initPadShot), initPadShot_stub);
    Utils::isTabletEnvironment = true;
    shot->startScreenshot();
    Utils::isTabletEnvironment = false;
    stub.reset(ADDR(MainWindow, initAttributes));
    stub.reset(ADDR(MainWindow, initResource));
    stub.reset(ADDR(MainWindow, initLaunchMode));
    stub.reset(ADDR(MainWindow, showFullScreen));
    stub.reset(ADDR(MainWindow, initPadShot));
}

void start_stub(int msec)
{

}
TEST_F(ScreenshotTest, delayScreenshot)
{
    stub.set((void(QTimer::*)())ADDR(QTimer, start), start_stub);
    stub.set(ADDR(MainWindow, initAttributes), initAttributes_stub1);
    stub.set(ADDR(MainWindow, initResource), initResource_stub1);
    stub.set(ADDR(MainWindow, initLaunchMode), initLaunchMode_stub1);
    stub.set(ADDR(MainWindow, showFullScreen), showFullScreen_stub1);

    shot->delayScreenshot(3);

    stub.reset((void(QTimer::*)())ADDR(QTimer, start));
    stub.reset(ADDR(MainWindow, initAttributes));
    stub.reset(ADDR(MainWindow, initResource));
    stub.reset(ADDR(MainWindow, initLaunchMode));
    stub.reset(ADDR(MainWindow, showFullScreen));

}

TEST_F(ScreenshotTest, fullscreenScreenshot)
{
    state = 0;
    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);
    stub.set(ADDR(Utils, passInputEvent), passInputEvent_stub_);
    stub.set(ADDR(QScreen, devicePixelRatio), devicePixelRatio_stub_1);
    stub.set(ADDR(QScreen, geometry), geometry_stub_);
    shot->fullscreenScreenshot();
    stub.reset(ADDR(QScreen, devicePixelRatio));
    stub.reset(ADDR(QScreen, geometry));
    stub.reset(ADDR(Utils, passInputEvent));
    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}

void noNotify_stub()
{

}
TEST_F(ScreenshotTest, noNotifyScreenshot_)
{
    state = 1;
    stub.set(ADDR(MainWindow, noNotify), noNotify_stub);

    shot->noNotifyScreenshot();

    stub.reset(ADDR(MainWindow, noNotify));

}

TEST_F(ScreenshotTest, noNotifyScreenshot)
{
    state = 2;
    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);

    stub.set(ADDR(Utils, passInputEvent), passInputEvent_stub_);
    stub.set(ADDR(QScreen, devicePixelRatio), devicePixelRatio_stub_1);
    stub.set(ADDR(QScreen, geometry), geometry_stub_);
    shot->fullscreenScreenshot();
    stub.reset(ADDR(QScreen, devicePixelRatio));
    stub.reset(ADDR(QScreen, geometry));
    stub.reset(ADDR(Utils, passInputEvent));

    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}

TEST_F(ScreenshotTest, clipboard_topWindowScreenshot)
{
    state = 3;
    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);

    stub.set(ADDR(Utils, passInputEvent), passInputEvent_stub_);
    stub.set(ADDR(QScreen, devicePixelRatio), devicePixelRatio_stub_1);
    stub.set(ADDR(QScreen, geometry), geometry_stub_);
    shot->topWindowScreenshot();
    stub.reset(ADDR(QScreen, devicePixelRatio));
    stub.reset(ADDR(QScreen, geometry));
    stub.reset(ADDR(Utils, passInputEvent));

    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}


TEST_F(ScreenshotTest, fullscreenScreenshot_)
{
    state = 4;
    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);

    stub.set(ADDR(Utils, passInputEvent), passInputEvent_stub_);
    stub.set(ADDR(QScreen, devicePixelRatio), devicePixelRatio_stub_1);
    stub.set(ADDR(QScreen, geometry), geometry_stub_);
    shot->fullscreenScreenshot();
    stub.reset(ADDR(QScreen, devicePixelRatio));
    stub.reset(ADDR(QScreen, geometry));
    stub.reset(ADDR(Utils, passInputEvent));

    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}

TEST_F(ScreenshotTest, topWindowScreenshot_)
{
    state = 5;
    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);

    stub.set(ADDR(Utils, passInputEvent), passInputEvent_stub_);
    stub.set(ADDR(QScreen, devicePixelRatio), devicePixelRatio_stub_1);
    stub.set(ADDR(QScreen, geometry), geometry_stub_);
    shot->topWindowScreenshot();
    stub.reset(ADDR(QScreen, devicePixelRatio));
    stub.reset(ADDR(QScreen, geometry));
    stub.reset(ADDR(Utils, passInputEvent));

    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}

TEST_F(ScreenshotTest, desktop_fullscreenScreenshot_)
{
    state = 6;
    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);

    stub.set(ADDR(Utils, passInputEvent), passInputEvent_stub_);
    stub.set(ADDR(QScreen, devicePixelRatio), devicePixelRatio_stub_1);
    stub.set(ADDR(QScreen, geometry), geometry_stub_);
    shot->fullscreenScreenshot();
    stub.reset(ADDR(QScreen, devicePixelRatio));
    stub.reset(ADDR(QScreen, geometry));
    stub.reset(ADDR(Utils, passInputEvent));

    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}

TEST_F(ScreenshotTest, clipboard_topWindowScreenshot_)
{
    state = 7;
    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);

    stub.set(ADDR(Utils, passInputEvent), passInputEvent_stub_);
    stub.set(ADDR(QScreen, devicePixelRatio), devicePixelRatio_stub_1);
    stub.set(ADDR(QScreen, geometry), geometry_stub_);
    shot->topWindowScreenshot();
    stub.reset(ADDR(QScreen, devicePixelRatio));
    stub.reset(ADDR(QScreen, geometry));
    stub.reset(ADDR(Utils, passInputEvent));

    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}

//TEST_F(ScreenshotTest, noNotifyScreenshot)
//{
//    stub.set(ADDR(Utils,passInputEvent),passInputEvent_stub_);
//    stub.set(ADDR(QScreen,devicePixelRatio),devicePixelRatio_stub_1);
//    stub.set(ADDR(QScreen,geometry),geometry_stub_);
//    shot->noNotifyScreenshot();
//    mwindow = access_private_field::Screenshotm_window(*shot);
//    QTest::mousePress(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(10,10));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseMove(mwindow, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseRelease(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    mwindow->saveScreenShot();
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    stub.reset(ADDR(QScreen,devicePixelRatio));
//    stub.reset(ADDR(QScreen,geometry));
//    stub.reset(ADDR(Utils,passInputEvent));

//    loop.exec();
//}

//TEST_F(ScreenshotTest, savePathScreenshot)
//{
//    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);
//    stub.set(ADDR(Utils,passInputEvent),passInputEvent_stub_);
//    stub.set(ADDR(QScreen,devicePixelRatio),devicePixelRatio_stub_1);
//    stub.set(ADDR(QScreen,geometry),geometry_stub_);
//    stub.set(ADDR(QWidget,width),width_stub);
//    stub.set(ADDR(QWidget,height),height_stub);

//    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//    shot->savePathScreenshot(path);
//    mwindow = access_private_field::Screenshotm_window(*shot);
//    QTest::mousePress(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(0,0));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseMove(mwindow, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseRelease(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    mwindow->saveScreenShot();
//    QTimer::singleShot(1000, &loop, SLOT(quit()));

//    stub.reset(ADDR(QScreen,devicePixelRatio));
//    stub.reset(ADDR(QScreen,geometry));
//    stub.reset(ADDR(Utils,passInputEvent));
//    stub.reset(ADDR(QWidget,width));
//    stub.reset(ADDR(QWidget,height));

//    loop.exec();
//}

//TEST_F(ScreenshotTest, startScreenshotFor3rd)
//{
//    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);
//    stub.set(ADDR(Utils,passInputEvent),passInputEvent_stub_);
//    stub.set(ADDR(QScreen,devicePixelRatio),devicePixelRatio_stub_1);
//    stub.set(ADDR(QScreen,geometry),geometry_stub_);
//    stub.set(ADDR(QWidget,width),width_stub);
//    stub.set(ADDR(QWidget,height),height_stub);

//    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//    shot->startScreenshotFor3rd(path);
//    mwindow = access_private_field::Screenshotm_window(*shot);
//    QTest::mousePress(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(0,0));


//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseMove(mwindow, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseRelease(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();

//    mwindow->saveScreenShot();

//    QTimer::singleShot(1000, &loop, SLOT(quit()));

//    stub.reset(ADDR(QScreen,devicePixelRatio));
//    stub.reset(ADDR(QScreen,geometry));
//    stub.reset(ADDR(Utils,passInputEvent));
//    stub.reset(ADDR(QWidget,width));
//    stub.reset(ADDR(QWidget,height));

//    loop.exec();
//}

//TEST_F(ScreenshotTest, startScreenshotFor3rd_Esc)
//{
//    stub.set(ADDR(ConfigSettings, value), getShotCfg_stub);
//    stub.set(ADDR(Utils,passInputEvent),passInputEvent_stub_);
//    stub.set(ADDR(QScreen,devicePixelRatio),devicePixelRatio_stub_1);
//    stub.set(ADDR(QScreen,geometry),geometry_stub_);
//    stub.set(ADDR(QWidget,width),width_stub);
//    stub.set(ADDR(QWidget,height),height_stub);

//    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//    shot->startScreenshotFor3rd(path);
//    mwindow = access_private_field::Screenshotm_window(*shot);
//    QTest::mousePress(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(0,0));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseMove(mwindow, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::mouseRelease(mwindow, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier, QPoint(800,400));
//    QTimer::singleShot(1000, &loop, SLOT(quit()));
//    loop.exec();
//    QTest::keyClick(mwindow, Qt::Key_Escape);
//    QTimer::singleShot(4000, &loop, SLOT(quit()));

//    stub.reset(ADDR(QScreen,devicePixelRatio));
//    stub.reset(ADDR(QScreen,geometry));
//    stub.reset(ADDR(Utils,passInputEvent));
//    stub.reset(ADDR(QWidget,width));
//    stub.reset(ADDR(QWidget,height));

//    loop.exec();
//}
TEST_F(ScreenshotTest, OcrScreenshot)
{
    stub.set(ADDR(MainWindow, initAttributes), initAttributes_stub1);
    stub.set(ADDR(MainWindow, initResource), initResource_stub1);
    stub.set(ADDR(MainWindow, initLaunchMode), initLaunchMode_stub1);
    stub.set(ADDR(MainWindow, showFullScreen), showFullScreen_stub1);

    shot->OcrScreenshot();

    stub.reset(ADDR(MainWindow, initAttributes));
    stub.reset(ADDR(MainWindow, initResource));
    stub.reset(ADDR(MainWindow, initLaunchMode));
    stub.reset(ADDR(MainWindow, showFullScreen));

}
TEST_F(ScreenshotTest, ScrollScreenshot)
{
    stub.set(ADDR(MainWindow, initAttributes), initAttributes_stub1);
    stub.set(ADDR(MainWindow, initResource), initResource_stub1);
    stub.set(ADDR(MainWindow, initLaunchMode), initLaunchMode_stub1);
    stub.set(ADDR(MainWindow, showFullScreen), showFullScreen_stub1);
    shot->ScrollScreenshot();
    stub.reset(ADDR(MainWindow, initAttributes));
    stub.reset(ADDR(MainWindow, initResource));
    stub.reset(ADDR(MainWindow, initLaunchMode));
    stub.reset(ADDR(MainWindow, showFullScreen));
}

void savePath_stub(QString path)
{
    Q_UNUSED(path);
}
TEST_F(ScreenshotTest, savePathScreenshot)
{
    stub.set(ADDR(MainWindow, savePath), savePath_stub);
    shot->savePathScreenshot("test");
    stub.reset(ADDR(MainWindow, savePath));
}

void startScreenshotFor3rd_stub(QString path)
{
    Q_UNUSED(path);
}
TEST_F(ScreenshotTest, startScreenshotFor3rd)
{
    stub.set(ADDR(MainWindow, startScreenshotFor3rd), startScreenshotFor3rd_stub);
    shot->startScreenshotFor3rd("test");
    stub.reset(ADDR(MainWindow, startScreenshotFor3rd));
}

TEST_F(ScreenshotTest, initLaunchMode)
{
    shot->initLaunchMode("screenshot");
}
void stopRecord_stub()
{

}
TEST_F(ScreenshotTest, stopRecord)
{
    stub.set(ADDR(MainWindow, stopRecord), stopRecord_stub);
    shot->startScreenshotFor3rd("test");
    stub.reset(ADDR(MainWindow, stopRecord));
}
QString getRecorderNormalIcon_stub()
{

    return "";
}
TEST_F(ScreenshotTest, getRecorderNormalIcon)
{
    stub.set(ADDR(RecorderTablet, getRecorderNormalIcon), getRecorderNormalIcon_stub);
    shot->getRecorderNormalIcon();
    stub.reset(ADDR(RecorderTablet, getRecorderNormalIcon));
}
