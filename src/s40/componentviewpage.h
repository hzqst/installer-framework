/**************************************************************************
**
** This file is part of Installer Framework
**
** Copyright (c) 2010-2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef COMPONENTVIEWPAGE_H
#define COMPONENTVIEWPAGE_H

#include <packagemanagergui.h>

QT_BEGIN_NAMESPACE
class QLabel;
class QString;
class QProgressBar;
class QModelIndex;
class QTreeView;
QT_END_NAMESPACE


namespace QInstaller {
    class ComponentModel;

class ComponentViewPage : public QInstaller::PackageManagerPage
{
    Q_OBJECT

public:
    explicit ComponentViewPage(QInstaller::PackageManagerCore *core);
    ~ComponentViewPage();

    void updateTreeView();

public slots:
   // void onCoreNetworkSettingsChanged();
    void setMessage(const QString &msg);
    void setErrorMessage(const QString &error);


public slots:
    void currentChanged(const QModelIndex &current);
    void selectComponent(const QString &id);
    void deselectComponent(const QString &id);

    void showInstalledComponents();
    void showUpdateNewComponents();

private:
    void fetchComponentsData();
    void fetchUpdateComponent();

private:
    bool m_updatesFetched;
    bool m_updatesCompleted;
    bool m_allPackagesFetched;

    QLabel *m_label;
    QProgressBar *m_progressBar;

    QPushButton* installButton;
    QPushButton* cancelButton;
    QLabel* showLabel;
    QLabel* progressStatusLabel;
    QLabel* progressLabel;
    QCheckBox*  showInstalled;
    QCheckBox* showUpdates;


    PackageManagerCore *m_core;
    QTreeView *m_treeView;
    ComponentModel *m_allModel;
    ComponentModel *m_updaterModel;
    ComponentModel *m_currentModel;
    QLabel *m_sizeLabel;
    QLabel *m_descriptionLabel;

};
} //namespace QInstaller

#endif // COMPONENTVIEWPAGE_H
