/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSystems module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qdeviceprofile.h>

#if defined(Q_OS_LINUX)
#  include "qdeviceprofile_linux_p.h"
#else
QT_BEGIN_NAMESPACE
class QDeviceProfilePrivate
{
public:
    QDeviceProfilePrivate(QDeviceProfile *) {}

    bool isVibrationActivated() { return false; }
    int messageRingtoneVolume() { return -1; }
    int voiceRingtoneVolume() { return -1; }
    QDeviceProfile::ProfileType currentProfileType() { return QDeviceProfile::UnknownProfile; }
};
QT_END_NAMESPACE
#endif

QT_BEGIN_NAMESPACE

/*!
    \class QDeviceProfile
    \inmodule QtSystemInfo
    \brief The QDeviceProfile class provides details for the profile of the device.
    \ingroup systeminfo
*/

/*!
    \enum QDeviceProfile::ProfileType
    This enum describes the type of the current profile.

    \value UnknownProfile    Profile unknown or on error.
    \value SilentProfile     Neither sound nor vibration is on.
    \value NormalProfile     Normal sound is on.
    \value VibrationProfile  Only vibration is on, and sound is off.
    \value BeepProfile       Only beep is on.
*/

/*!
    \fn void QDeviceProfile::currentProfileTypeChanged(ProfileType profile)

    This signal is emitted whenever the current profile type has been changed to \a profile.
 */

/*!
    Constructs a QDeviceProfile object with the given \a parent.
*/
QDeviceProfile::QDeviceProfile(QObject *parent)
    : QObject(parent)
    , d_ptr(new QDeviceProfilePrivate(this))
{
}

/*!
    Destroys the object
*/
QDeviceProfile::~QDeviceProfile()
{
    delete d_ptr;
}

/*!
    Returns the whether the vibration is active for this profile.
*/
bool QDeviceProfile::isVibrationActivated() const
{
    return d_ptr->isVibrationActivated();
}

/*!
    Returns the message ringtone volume for this profile, from 0 to 100. If this information is unknown,
    or error occurs, -1 is returned.
*/
int QDeviceProfile::messageRingtoneVolume() const
{
    return d_ptr->messageRingtoneVolume();
}

/*!
    Returns the voice ringtone volume for this profile, from 0 to 100. If this information is unknown,
    or error occurs, -1 is returned.
*/
int QDeviceProfile::voiceRingtoneVolume() const
{
    return d_ptr->voiceRingtoneVolume();
}

/*!
    \property QDeviceProfile::currentProfileType
    \brief The current activated profile.

    Returns the type for this profile.
*/
QDeviceProfile::ProfileType QDeviceProfile::currentProfileType() const
{
    return d_ptr->currentProfileType();
}

QT_END_NAMESPACE
