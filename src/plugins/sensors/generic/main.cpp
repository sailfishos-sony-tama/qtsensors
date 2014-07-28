/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
#include "genericorientationsensor.h"
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
#include "genericrotationsensor.h"
#endif
#ifdef QTSENSORS_GENERICALSSENSOR
#include "genericalssensor.h"
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
#include "generictiltsensor.h"
#endif
#ifdef QTSENSORS_GENERICCOMPASS
#include "genericcompass.h"
#endif
#include <QtSensors/qsensorplugin.h>
#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qsensormanager.h>
#include <QFile>
#include <QDebug>

class genericSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorChangesInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface QSensorChangesInterface)
public:
    void registerSensors() Q_DECL_OVERRIDE
    {
        // Nothing to register here
    }

    void sensorsChanged() Q_DECL_OVERRIDE
    {
        if (!QSensor::defaultSensorForType(QAccelerometer::type).isEmpty()) {
            // There is an accelerometer available. Register the backends
#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
            if (!QSensorManager::isBackendRegistered(QOrientationSensor::type, genericorientationsensor::id))
                QSensorManager::registerBackend(QOrientationSensor::type, genericorientationsensor::id, this);
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
            if (!QSensorManager::isBackendRegistered(QRotationSensor::type, genericrotationsensor::id))
                QSensorManager::registerBackend(QRotationSensor::type, genericrotationsensor::id, this);
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
            if (!QSensorManager::isBackendRegistered(QTiltSensor::type, GenericTiltSensor::id))
                QSensorManager::registerBackend(QTiltSensor::type, GenericTiltSensor::id, this);
#endif
#ifdef QTSENSORS_GENERICCOMPASS
            if (!QSensor::defaultSensorForType(QMagnetometer::type).isEmpty()
                    && !QSensor::defaultSensorForType(QGyroscope::type).isEmpty()) {
                if (!QSensorManager::isBackendRegistered(QCompass::type, GenericCompass::id)) {
                    QSensorManager::registerBackend(QCompass::type, GenericCompass::id, this);
                }
            }
#endif
        } else {
#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
            if (QSensorManager::isBackendRegistered(QOrientationSensor::type, genericorientationsensor::id))
                QSensorManager::unregisterBackend(QOrientationSensor::type, genericorientationsensor::id);
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
            if (QSensorManager::isBackendRegistered(QRotationSensor::type, genericrotationsensor::id))
                QSensorManager::unregisterBackend(QRotationSensor::type, genericrotationsensor::id);
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
            if (QSensorManager::isBackendRegistered(QTiltSensor::type, GenericTiltSensor::id))
                QSensorManager::unregisterBackend(QTiltSensor::type, GenericTiltSensor::id);
#endif
#ifdef QTSENSORS_GENERICCOMPASS
            if (QSensorManager::isBackendRegistered(QCompass::type, GenericCompass::id))
                QSensorManager::unregisterBackend(QCompass::type, GenericCompass::id);
#endif
        }

        if (!QSensor::defaultSensorForType(QLightSensor::type).isEmpty()) {
#ifdef QTSENSORS_GENERICALSSENSOR
            if (!QSensorManager::isBackendRegistered(QAmbientLightSensor::type, genericalssensor::id))
                QSensorManager::registerBackend(QAmbientLightSensor::type, genericalssensor::id, this);
#endif
        } else {
#ifdef QTSENSORS_GENERICALSSENSOR
            if (QSensorManager::isBackendRegistered(QAmbientLightSensor::type, genericalssensor::id))
                QSensorManager::unregisterBackend(QAmbientLightSensor::type, genericalssensor::id);
#endif
        }
    }

    QSensorBackend *createBackend(QSensor *sensor) Q_DECL_OVERRIDE
    {
#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
        if (sensor->identifier() == genericorientationsensor::id)
            return new genericorientationsensor(sensor);
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
        if (sensor->identifier() == genericrotationsensor::id)
            return new genericrotationsensor(sensor);
#endif
#ifdef QTSENSORS_GENERICALSSENSOR
        if (sensor->identifier() == genericalssensor::id)
            return new genericalssensor(sensor);
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
        if (sensor->identifier() == GenericTiltSensor::id)
            return new GenericTiltSensor(sensor);
#endif
#ifdef QTSENSORS_GENERICCOMPASS
        if (sensor->identifier() == GenericCompass::id)
            return new GenericCompass(sensor);
#endif
        return 0;
    }
};

#include "main.moc"

