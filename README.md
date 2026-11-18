# Lilashape
[English](#english) · [Español](#español)

## English


Legacy Windows interface for viewing modes and sending settings to equipment over a serial port

> [!WARNING]
> **Status: Legacy.** The Win32 code builds with v145. Its original interface needs the retired Flash ActiveX control.

### Overview

Lilashape is a desktop panel for equipment connected to a Windows PC by a serial port. A Flash movie provides the screens and sends commands to the C++ app. The app translates user selections into serial messages.

### Features

- Enter and save the port name in the configuration dialog. If the initial connection fails, the application can retry from that dialog.
- The original movie’s controls select a mode, change settings such as infrared, radio frequency and suction, and switch the operating state.
- The app reads serial responses and updates indicators in the movie.

### Requirements

Windows 11 with Desktop development with C++ and MFC Win32. Verified with Visual Studio Community 2026 18.11.4, MSBuild 18.11.1.51303, MSVC v145 14.51.36231, Windows SDK 10.0.26100.0. The solution compiles the included Serial library source. The historical interface needs the x86 Adobe Flash ActiveX control, original version unknown, and the included `media/lilashape.swf`. The FLA identifies its editor as Adobe Flash CS4 Professional for Windows 10.0 build 544. The verification used the archived SWF export. Adobe ended support and removed public downloads for the ActiveX control. A functional serial test also needs the original equipment and a compatible serial connection.

### Getting started

Build from the root in Developer PowerShell for Visual Studio. The second line invokes the original program, which exits without opening its dialog on the verified Windows installation.

```powershell
MSBuild lilashape.sln /m:2 /t:Rebuild /p:Configuration=Release /p:Platform=Win32 /p:PreferredToolArchitecture=x64
.\Release\lilashape.exe
```

### Usage

In a compatible historical environment the application looks for `lilashape.swf` next to the executable. Copy the archived media/lilashape.swf to the executable folder. The editable source remains in media/LilaShape.fla. The film and C++ exchange commands through Flash ActiveX.

For a fictional walkthrough with the equipment disconnected, start the program with a port name that has no device attached. When the initial connection fails, enter another unused name, such as `COM215`, in the port dialog and confirm with **Aceptar**. The program retries and reports that the port could not be opened. The film can still play in the dialog if Flash ActiveX and the SWF are available. A standalone player provides a separate way to inspect its opening screen. Verifying serial exchange requires the original equipment.

[Adobe’s end-of-life notice](https://www.adobe.com/products/flashplayer/end-of-life.html)

### Project structure

`lilashapeDlg.cpp` contains the port configuration, commands and response handling. `shockwaveflash1.*` wraps the external COM control. The application project builds the source in `Serial/`, where the original and converted Serial projects are available. `res/` holds the icon and Win32 resources, `media/LilaShape.fla` is the movie’s editable source, `LICENSES/` contains the LGPL text, and `lilashape.legacy.sln` is the original application solution.

### Contributing

Describe the source version and build command when reporting an issue. Use a fictional test profile.

### Support

Use the repository’s Issues to record reproducible build or startup problems.

### History

The source snapshot dates to March 18, 2009. The 2026 reconstruction restores the Serial source, wrapper, editable movie and icon from the archive, converts the Win32 solution and documents the obsolete runtime. The archived SWF from the original executable folder is included in media/.

### Verification

On November 19, 2026, `MSBuild lilashape.sln /m:2 /t:Rebuild /p:Configuration=Release /p:Platform=Win32 /p:PreferredToolArchitecture=x64` built both snapshots in separate directories on Windows 11 Pro build 26300 with Visual Studio Community 2026 18.11.4, MSBuild 18.11.1.51303, MSVC v145 14.51.36231, Windows SDK 10.0.26100.0. `Release\lilashape.exe` returned 0 without opening its dialog. The x86 Flash ActiveX class is missing from the host. The test selected COM215 after checking that the name had no assigned device. It sent no commands to equipment. The start screen of the archived movie appeared separately in Ruffle 0.7.1, Chrome 157.0.8103.51 headless and a disposable HTTP container in Docker Engine 29.9.2 on loopback. That check covered the opening screen. Win32 dialog events and serial exchange remain unverified.

### License

The [MIT License](LICENSE) covers the application’s own code. The [third-party notices](THIRD-PARTY-NOTICES.md) list the respective components.

---

## Español


Interfaz legada para Windows que muestra modos y envía ajustes a un equipo por puerto serie

> [!WARNING]
> **Estado: legado.** El código Win32 compila con v145. Su interfaz original requiere el control Flash ActiveX retirado.

### Descripción general

Lilashape es un panel de escritorio para un equipo conectado a un PC con Windows por puerto serie. Una película Flash proporciona las pantallas y envía órdenes a la aplicación C++. La aplicación traduce las selecciones en mensajes por el puerto.

### Funciones

- Escribe y guarda el nombre del puerto en el cuadro de configuración. Si falla la conexión inicial, la aplicación puede reintentar desde ese cuadro.
- Los controles de la película original permiten elegir un modo, cambiar ajustes como infrarrojo, radiofrecuencia y succión, y cambiar el estado de funcionamiento.
- La aplicación lee las respuestas serie y actualiza los indicadores de la película.

### Requisitos

Windows 11 con Desarrollo para el escritorio con C++ y MFC para Win32. Verificado con Visual Studio Community 2026 18.11.4, MSBuild 18.11.1.51303, MSVC v145 14.51.36231, Windows SDK 10.0.26100.0. La solución compila los fuentes incluidos de la biblioteca Serial. La interfaz histórica requiere el control Adobe Flash ActiveX x86, de versión original desconocida, y el `media/lilashape.swf` incluido. El FLA identifica su editor como Adobe Flash CS4 Professional para Windows 10.0 build 544. La verificación usó la exportación SWF del respaldo. Adobe retiró el soporte y las descargas públicas del control ActiveX. Una prueba funcional del puerto requiere además el equipo original y una conexión serie compatible.

### Cómo empezar

Compila desde la raíz en Developer PowerShell para Visual Studio. La segunda línea invoca el programa original, que termina sin abrir su ventana en la instalación de Windows verificada.

```powershell
MSBuild lilashape.sln /m:2 /t:Rebuild /p:Configuration=Release /p:Platform=Win32 /p:PreferredToolArchitecture=x64
.\Release\lilashape.exe
```

### Uso

En un entorno histórico compatible, la aplicación busca `lilashape.swf` junto al ejecutable. Copia media/lilashape.swf junto al ejecutable. La fuente editable queda en media/LilaShape.fla. La película y el C++ intercambian órdenes por Flash ActiveX.

Para un recorrido ficticio con el equipo desconectado, inicia el programa con un nombre de puerto sin dispositivo conectado. Si falla la conexión inicial, indica otro nombre sin dispositivo, como `COM215`, en el cuadro de puerto y confirma con **Aceptar**. El programa reintenta la conexión y avisa que el puerto no se pudo abrir. La película puede reproducirse en la ventana si están disponibles Flash ActiveX y el SWF. Un reproductor independiente permite examinar por separado su pantalla inicial. Verificar el intercambio por puerto serie requiere el equipo original.

[Aviso de fin de vida de Adobe](https://www.adobe.com/products/flashplayer/end-of-life.html)

### Estructura del proyecto

`lilashapeDlg.cpp` contiene la configuración del puerto, las órdenes y el tratamiento de respuestas. `shockwaveflash1.*` envuelve el control COM externo. El proyecto de la aplicación compila los fuentes de `Serial/`, que conserva los proyectos original y convertido de Serial. `res/` contiene el icono y los recursos Win32, `media/LilaShape.fla` es el archivo editable de la película, `LICENSES/` contiene el texto LGPL y `lilashape.legacy.sln` es la solución original de la aplicación.

### Contribuir

Al reportar un problema, indica la versión de los fuentes y el comando de compilación. Usa un perfil de prueba ficticio.

### Soporte

Usa Issues del repositorio para registrar problemas reproducibles de compilación o arranque.

### Historia

La versión de los fuentes es del 18 de marzo de 2009. La reconstrucción de 2026 recupera del respaldo los fuentes de Serial, el envoltorio, la película editable y el icono, convierte la solución Win32 y documenta el entorno de ejecución obsoleto. Se incluye en media/ el SWF que acompañaba al ejecutable del respaldo.

### Verificación

El 19 de noviembre de 2026, `MSBuild lilashape.sln /m:2 /t:Rebuild /p:Configuration=Release /p:Platform=Win32 /p:PreferredToolArchitecture=x64` compiló ambas versiones en carpetas separadas en Windows 11 Pro compilación 26300 con Visual Studio Community 2026 18.11.4, MSBuild 18.11.1.51303, MSVC v145 14.51.36231, Windows SDK 10.0.26100.0. `Release\lilashape.exe` devolvió 0 sin abrir su ventana. El equipo carece de la clase Flash ActiveX x86. La prueba seleccionó COM215 después de comprobar que ese nombre carecía de dispositivo. No envió órdenes a ningún equipo. La pantalla inicial de la película del respaldo apareció por separado en Ruffle 0.7.1, Chrome 157.0.8103.51 sin interfaz y un contenedor HTTP desechable en Docker Engine 29.9.2 en la interfaz local. Esa prueba cubrió la pantalla de inicio. Quedan sin verificar los eventos del diálogo Win32 y el intercambio serie.

### Licencia

La [licencia MIT](LICENSE) cubre el código propio de la aplicación. Los [avisos de terceros](THIRD-PARTY-NOTICES.md) identifican sus componentes.
