/****************************************************************************
**
** Copyright (C) 2013 Klaralvdalens Datakonsult AB (KDAB)
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Installer Framework.
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

#ifndef KD_UPDATER_UPDATE_OPERATIONS_H
#define KD_UPDATER_UPDATE_OPERATIONS_H

#include "kdupdaterupdateoperation.h"

namespace KDUpdater {

class KDTOOLS_EXPORT CopyOperation : public UpdateOperation
{
public:
    CopyOperation();
    ~CopyOperation();

    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    CopyOperation *clone() const;

    QDomDocument toXml() const;
private:
    QString sourcePath();
    QString destinationPath();
};

class KDTOOLS_EXPORT MoveOperation : public UpdateOperation
{
public:
    MoveOperation();
    ~MoveOperation();

    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    MoveOperation *clone() const;
};

class KDTOOLS_EXPORT DeleteOperation : public UpdateOperation
{
public:
    DeleteOperation();
    ~DeleteOperation();

    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    DeleteOperation *clone() const;

    QDomDocument toXml() const;
};

class KDTOOLS_EXPORT MkdirOperation : public UpdateOperation
{
public:
    MkdirOperation();

    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    MkdirOperation *clone() const;
};

class KDTOOLS_EXPORT RmdirOperation : public UpdateOperation
{
public:
    RmdirOperation();

    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    RmdirOperation *clone() const;
};

class KDTOOLS_EXPORT AppendFileOperation : public UpdateOperation
{
public:
    AppendFileOperation();

    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    AppendFileOperation *clone() const;
};

class KDTOOLS_EXPORT PrependFileOperation : public UpdateOperation
{
public:
    PrependFileOperation();

    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    PrependFileOperation *clone() const;
};

} // namespace KDUpdater

#endif // KD_UPDATER_UPDATE_OPERATIONS_H
