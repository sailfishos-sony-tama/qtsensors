/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
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

#include "sensorfwrotationsensor.h"

char const * const SensorfwRotationSensor::id("sensorfw.rotationsensor");

SensorfwRotationSensor::SensorfwRotationSensor(QSensor *sensor)
    : SensorfwSensorBase(sensor)
    , m_initDone(0)
{
    init();
    setReading<QRotationReading>(&m_reading);
    QRotationSensor *const rotationSensor = qobject_cast<QRotationSensor *>(sensor);
    if (rotationSensor)
        rotationSensor->setHasZ(true);
    sensor->setDataRate(20);//set a default rate
}

void SensorfwRotationSensor::slotDataAvailable(const XYZ& data)
{
    m_reading.setFromEuler(data.x(),data.y(),data.z());
    m_reading.setTimestamp(data.XYZData().timestamp_);
    newReadingAvailable();
}

void SensorfwRotationSensor::slotFrameAvailable(const QVector<XYZ>&  frame)
{
    for (int i=0, l=frame.size(); i<l; i++) {
        slotDataAvailable(frame.at(i));
    }
}

bool SensorfwRotationSensor::doConnect()
{
    Q_ASSERT(m_sensorInterface);
    if (m_bufferSize==1)
       return QObject::connect(m_sensorInterface, SIGNAL(dataAvailable(const XYZ&)), this, SLOT(slotDataAvailable(const XYZ&)));
    return QObject::connect(m_sensorInterface, SIGNAL(frameAvailable(const QVector<XYZ>& )),this, SLOT(slotFrameAvailable(const QVector<XYZ>& )));
}

QString SensorfwRotationSensor::sensorName() const
{
    return "rotationsensor";
}

void SensorfwRotationSensor::init()
{
    m_initDone = false;
    initSensor<RotationSensorChannelInterface>(m_initDone);
}
