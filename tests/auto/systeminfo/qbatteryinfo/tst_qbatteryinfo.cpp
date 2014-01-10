/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Copyright (C) 2014 BlackBerry Limited. All rights reserved.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSystems module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include "qbatteryinfo.h"

QT_USE_NAMESPACE

class tst_QBatteryInfo : public QObject
{
    Q_OBJECT

private slots:
    void tst_capacity();
    void tst_flow();
    void tst_invalid();
    void tst_setBatteryIndex();
};

void tst_QBatteryInfo::tst_capacity()
{
    QBatteryInfo batteryInfo;

    int count = batteryInfo.batteryCount();
    for (int i = 0; i < count; ++i) {
        batteryInfo.setBatteryIndex(i);
        int max = batteryInfo.maximumCapacity();
        int remaining = batteryInfo.remainingCapacity();

        QVERIFY(max == -1 || remaining == -1 || remaining <= max);
    }
}

void tst_QBatteryInfo::tst_flow()
{
    QBatteryInfo batteryInfo;

    int count = batteryInfo.batteryCount();
    for (int i = 0; i < count; ++i) {
        batteryInfo.setBatteryIndex(i);
        QBatteryInfo::ChargingState chargingState = batteryInfo.chargingState();
        switch (chargingState) {
        case QBatteryInfo::Charging:
            QVERIFY(batteryInfo.currentFlow() < 0);
            QVERIFY(batteryInfo.remainingChargingTime() >= 0);
            break;
        case QBatteryInfo::IdleChargingState:
            QVERIFY(batteryInfo.currentFlow() >= 0);
            QVERIFY(batteryInfo.remainingChargingTime() == 0);
            break;
        case QBatteryInfo::Discharging:
            QVERIFY(batteryInfo.currentFlow() > 0);
            QVERIFY(batteryInfo.remainingChargingTime() == 0);
            break;
        case QBatteryInfo::UnknownChargingState:
            QVERIFY(batteryInfo.currentFlow() == 0);
            QVERIFY(batteryInfo.remainingChargingTime() == -1);
            break;
        }
    }
}

void tst_QBatteryInfo::tst_invalid()
{
    QBatteryInfo batteryInfo;

    batteryInfo.setBatteryIndex(-1);
    QVERIFY(batteryInfo.currentFlow() == 0);
    QVERIFY(batteryInfo.maximumCapacity() == -1);
    QVERIFY(batteryInfo.remainingCapacity() == -1);
    QVERIFY(batteryInfo.remainingChargingTime() == -1);
    QVERIFY(batteryInfo.voltage() == -1);
    QVERIFY(batteryInfo.chargingState() == QBatteryInfo::UnknownChargingState);
    QVERIFY(batteryInfo.levelStatus() == QBatteryInfo::LevelUnknown);

    int count = batteryInfo.batteryCount();
    batteryInfo.setBatteryIndex(count);
    QVERIFY(batteryInfo.currentFlow() == 0);
    QVERIFY(batteryInfo.maximumCapacity() == -1);
    QVERIFY(batteryInfo.remainingCapacity() == -1);
    QVERIFY(batteryInfo.remainingChargingTime() == -1);
    QVERIFY(batteryInfo.voltage() == -1);
    QVERIFY(batteryInfo.chargingState() == QBatteryInfo::UnknownChargingState);
    QVERIFY(batteryInfo.levelStatus() == QBatteryInfo::LevelUnknown);
}

void tst_QBatteryInfo::tst_setBatteryIndex()
{
    QBatteryInfo batteryInfo;

    QCOMPARE(batteryInfo.batteryIndex(), 0);

    batteryInfo.setBatteryIndex(1);
    QCOMPARE(batteryInfo.batteryIndex(), 1);

    batteryInfo.setBatteryIndex(1000);
    QCOMPARE(batteryInfo.batteryIndex(), 1000);

    batteryInfo.setBatteryIndex(-1);
    QCOMPARE(batteryInfo.batteryIndex(), -1);
}

QTEST_MAIN(tst_QBatteryInfo)
#include "tst_qbatteryinfo.moc"
