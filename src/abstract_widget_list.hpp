/**
  
\file

\author Mattia Basaglia

\section License
This file is part of Knotter.

Copyright (C) 2012-2014  Mattia Basaglia

Knotter is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Knotter is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef ABSTRACT_WIDGET_LIST_HPP
#define ABSTRACT_WIDGET_LIST_HPP

#include <QSignalMapper>
#include <QTableWidget>

class Abstract_Widget_List : public QWidget
{
    Q_OBJECT

private:
    QList<QWidget*> widgets;
    QSignalMapper mapper_up;
    QSignalMapper mapper_down;
    QSignalMapper mapper_remove;
    QTableWidget*table;

public:
    explicit Abstract_Widget_List(QWidget *parent = 0);
    
    /**
     *  \brief Get the number of items
     */
    int count() const { return widgets.size(); }

    /**
     *  \brief Swap row a and row b
     */
    virtual void swap(int a, int b) = 0;


    /// Whether the given row index is valid
    bool isValidRow(int i) const { return i >= 0 && i < count(); }

    void setRowHeight(int row, int height);


public slots:
    /**
     *  \brief Remove row i
     */
    void remove(int i);

    /**
     *  \brief append a default row
     */
    virtual void append() = 0;

signals:
    void removed(int i);

protected:

    /**
     *  \brief Create a new row with the given widget
     *
     *  Must be caled by implementations of append()
     */
    void appendWidget(QWidget* w);

    /**
     *  \brief get the widget found at the given row
     */
    QWidget* widget(int i);


    /**
     *  \brief get the widget found at the given row
     */
    template<class T>
    T* widget_cast(int i) { return qobject_cast<T*>(widget(i)); }

    /**
     *  \brief clear all rows without emitting signals
     *
     *  May be useful when implementation want to set all values at once
     */
    void clear();

private:
    QWidget* create_button(QWidget* data, QSignalMapper*mapper,
                           QString icon_name, QString text,
                           QString tooltip = QString()) const;

private slots:
    void remove_clicked(QWidget* w);
    void up_clicked(QWidget* w);
    void down_clicked(QWidget* w);
};

#endif // ABSTRACT_WIDGET_LIST_HPP
