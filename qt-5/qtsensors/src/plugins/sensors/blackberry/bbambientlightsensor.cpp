/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
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
#include "bbambientlightsensor.h"

BbAmbientLightSensor::BbAmbientLightSensor(QSensor *sensor)
    : BbSensorBackend<QAmbientLightReading>(devicePath(), SENSOR_TYPE_LIGHT, sensor)
{
    setDescription(QLatin1String("Ambient light brightness"));
}

bool BbAmbientLightSensor::updateReadingFromEvent(const sensor_event_t &event, QAmbientLightReading *reading)
{
    const int lightLevelLux = event.light_s.illuminance;
    if (lightLevelLux < 10)
        reading->setLightLevel(QAmbientLightReading::Dark);
    else if (lightLevelLux < 80)
        reading->setLightLevel(QAmbientLightReading::Twilight);
    else if (lightLevelLux < 400)
        reading->setLightLevel(QAmbientLightReading::Light);
    else if (lightLevelLux < 2500)
        reading->setLightLevel(QAmbientLightReading::Bright);
    else
        reading->setLightLevel(QAmbientLightReading::Sunny);

    return true;
}

QString BbAmbientLightSensor::devicePath()
{
    return QLatin1String("/dev/sensor/light");
}
