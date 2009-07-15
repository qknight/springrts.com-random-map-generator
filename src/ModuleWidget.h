//
// C++ Interface:
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef MODULEWIDGET_H
#define MODULEWIDGET_H

#include <QWidget>
#include "ui_moduleWidget.h"

class ModuleWidget : public QWidget, private Ui::moduleWidget
{
  Q_OBJECT

public:
  ModuleWidget(QWidget* parent = 0 );
  ~ModuleWidget();
  /*$PUBLIC_FUNCTIONS$*/

public slots:
  /*$PUBLIC_SLOTS$*/

protected:
  /*$PROTECTED_FUNCTIONS$*/

protected slots:
  /*$PROTECTED_SLOTS$*/

};

#endif

