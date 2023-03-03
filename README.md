![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=fff&style=plastic) ![MQTT Badge](https://img.shields.io/badge/MQTT-606?logo=mqtt&logoColor=fff&style=plastic) ![](https://badgen.net/badge/Qt/5.12.8/green) ![Android Badge](https://img.shields.io/badge/Android-3DDC84?logo=android&logoColor=fff&style=plastic)

[![pages-build-deployment](https://github.com/btssn-lasalle-84/eco-classroom-2023/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/btssn-lasalle-84/eco-classroom-2023/actions/workflows/pages/pages-build-deployment)

# Le projet eco-classroom-2023

- [Le projet eco-classroom-2023](#le-projet-eco-classroom-2023)
  - [MQTT](#mqtt)
    - [Qt MQTT](#qt-mqtt)
    - [Paho MQTT (Android)](#paho-mqtt-android)

## MQTT

Voir aussi : [modules-lora/README.md](modules-lora/README.md)

### Qt MQTT

[Qt MQTT](https://doc.qt.io/QtMQTT/index.html) fournit une implémentation conforme à la norme MQTT.

Qt MQTT fait parti de [Qt For Automation](http://doc.qt.io/QtForAutomation/qtautomation-overview.html) et pas directement de Qt. Il faut donc l'installer.

Installation :

1. Identifier la version de Qt :

```sh
$ qmake -v
QMake version 3.1
Using Qt version 5.12.8 in /usr/lib/x86_64-linux-gnu
```

Ici, la version de Qt est `5.12.8`.

2. Récupérer le code source du module `mqtt` en clonant le dépôt git

```sh
$ sudo git clone https://code.qt.io/qt/qtmqtt.git
$ cd qtmqtt/
```

3. Sélectionner la branche qui correspond à la version de Qt utilisée

```sh
$ sudo git checkout 5.12.8
```

4. Installer le paquet fournissant les fichiers d'en-tête de développement indépendants

```sh
$ sudo apt install qtbase5-private-dev
```

5. Fabriquer et installer le module `mqtt`

```sh
$ sudo qmake

$ sudo make

$ sudo make install
```

Pour accèder aux classes du module Qt MQTT, il faudra ajouter le module `mqtt` au fichier de projet `.pro` :

```
QT += mqtt
```

### Paho MQTT (Android)

Il faut ajouter les dépendances vers les bibliothèques nécessaires à l’utilisation du protocole MQTT : le client Paho MQTT et le service Android fournis par Eclipse.

Liens : [Eclipse Paho](https://www.eclipse.org/paho/) et [github](https://github.com/eclipse/paho.mqtt.java)

1. Il faut ajouter l’url d’Eclipse Paho dans le ficher `build.gradle` du projet :

```
buildscript {
    repositories {
        google()
        jcenter()
    }
    dependencies {
        classpath 'com.android.tools.build:gradle:3.1.3'
        // NOTE: Do not place your application dependencies here; they belong
        // in the individual module build.gradle files
    }
}

allprojects {
    repositories {
        google()
        jcenter()
        maven {
            url "https://repo.eclipse.org/content/repositories/paho-snapshots/"
        }
    }
}

task clean(type: Delete) {
    delete rootProject.buildDir
}
```

2. Puis, il faut ajouter les dépendances vers le client Paho MQTT et le service Android dans le fichier build.gradle du dossier `app` :

```
...
dependencies {
    ...

    implementation 'org.eclipse.paho:org.eclipse.paho.client.mqttv3:1.1.0'
    implementation 'org.eclipse.paho:org.eclipse.paho.android.service:1.1.1'
    implementation 'androidx.localbroadcastmanager:localbroadcastmanager:1.0.0'
}
```

3. L’utilisation du protocole MQTT suppose que l’on ait un accès réseau. Pour cela, on va attribuer les permissions `INTERNET`, `ACCESS_NETWORK_STATE`, `ACCESS_WIFI_STATE` et `WAKE_LOCK` à l’application Android dans son fichier `AndroidManifest.xml`. On ajoutera aussi le service `MqttService`.

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    ...>

    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
    <uses-permission android:name="android.permission.WAKE_LOCK"/>

    <application
        ...>
        ...
        <service android:name="org.eclipse.paho.android.service.MqttService" />
    </application>

</manifest>
```

---
©️ LaSalle Avignon 2023
