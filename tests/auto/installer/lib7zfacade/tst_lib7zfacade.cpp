/**************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://qt.io/terms-conditions. For further
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
**
** $QT_END_LICENSE$
**
**************************************************************************/

#include <lib7z_create.h>
#include <lib7z_extract.h>
#include <lib7z_facade.h>
#include <lib7z_list.h>

#include <QDir>
#include <QObject>
#include <QTemporaryFile>
#include <QTest>

class tst_lib7zfacade : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        Lib7z::initSevenZ();

        m_file.path = "valid";
        m_file.permissions = 0;
        m_file.compressedSize = 836;
        m_file.uncompressedSize = 5242880;
        m_file.isDirectory = false;
        m_file.archiveIndex = QPoint(0, 0);
        m_file.mtime = QDateTime(QDate::fromJulianDay(2456413), QTime(12, 50, 42));
    }

    void testIsSupportedArchive()
    {
        QCOMPARE(Lib7z::isSupportedArchive(":///data/valid.7z"), true);
        QCOMPARE(Lib7z::isSupportedArchive(":///data/invalid.7z"), false);

        try {
            QFile file(":///data/valid.7z");
            QVERIFY(file.open(QIODevice::ReadOnly));
            QCOMPARE(Lib7z::isSupportedArchive(&file), true);
        } catch (...) {
            QFAIL("Unexpected error during Lib7z::isSupportedArchive.");
        }

        try {
            QFile file(":///data/invalid.7z");
            QVERIFY(file.open(QIODevice::ReadOnly));
            QCOMPARE(Lib7z::isSupportedArchive(&file), false);
        } catch (...) {
            QFAIL("Unexpected error during Lib7z::isSupportedArchive.");
        }
    }

    void testListArchive()
    {
        try {
            QFile file(":///data/valid.7z");
            QVERIFY(file.open(QIODevice::ReadOnly));

            QVector<Lib7z::File> files = Lib7z::listArchive(&file);
            QCOMPARE(files.count(), 1);
            QCOMPARE(files.first(), m_file);
        } catch (...) {
            QFAIL("Unexpected error during list archive.");
        }

        try {
            QFile file(":///data/invalid.7z");
            QVERIFY(file.open(QIODevice::ReadOnly));
            QVector<Lib7z::File> files = Lib7z::listArchive(&file);
        } catch (const Lib7z::SevenZipException& e) {
            QCOMPARE(e.message(), QString("Cannot open archive \":///data/invalid.7z\"."));
        } catch (...) {
            QFAIL("Unexpected error during list archive.");
        }
    }

    void testCreateArchive()
    {
        try {
            const QString path = tempSourceFile("Source File 1.");
            const QString path2 = tempSourceFile("Source File 2.");

            QTemporaryFile target;
            QVERIFY(target.open());
            Lib7z::createArchive(&target, QStringList() << path << path2);
            QCOMPARE(Lib7z::listArchive(&target).count(), 2);
        } catch (const Lib7z::SevenZipException& e) {
            QFAIL(e.message().toUtf8());
        } catch (...) {
            QFAIL("Unexpected error during create archive.");
        }

        try {
            const QString path1 = tempSourceFile(
                "Source File 1.",
                QDir::tempPath() + "/temp file with spaces.XXXXXX"
            );
            const QString path2 = tempSourceFile(
                "Source File 2.",
                QDir::tempPath() + "/temp file with spaces.XXXXXX"
            );

            QTemporaryFile target(QDir::tempPath() + "/target file with spaces.XXXXXX");
            QVERIFY(target.open());
            Lib7z::createArchive(&target, QStringList() << path1 << path2);
            QCOMPARE(Lib7z::listArchive(&target).count(), 2);
        } catch (const Lib7z::SevenZipException& e) {
            QFAIL(e.message().toUtf8());
        } catch (...) {
            QFAIL("Unexpected error during create archive.");
        }

    }

    void testExtractArchive()
    {
        QFile source(":///data/valid.7z");
        QVERIFY(source.open(QIODevice::ReadOnly));

        try {
            Lib7z::extractArchive(&source, QDir::tempPath());
            QCOMPARE(QFile::exists(QDir::tempPath() + QString("/valid")), true);
        } catch (const Lib7z::SevenZipException& e) {
            QFAIL(e.message().toUtf8());
        } catch (...) {
            QFAIL("Unexpected error during extract archive.");
        }
    }

private:
    QString tempSourceFile(const QByteArray &data, const QString &templateName = QString())
    {
        QTemporaryFile source;
        if (!templateName.isEmpty()) {
            source.setFileTemplate(templateName);
        }
        source.open();
        source.write(data);
        source.setAutoRemove(false);
        return source.fileName();
    }

private:
    Lib7z::File m_file;
};

QTEST_MAIN(tst_lib7zfacade)

#include "tst_lib7zfacade.moc"
