/*
    Scale - An shell for Pandora, a handheld gaming device.
    Copyright (C) 2008 Zoxc

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "List.hpp"

List::List() :
    Count(0),
    Capacity(0),
    Items(0)
{
}

List::~List()
{
    SetCapacity(0);
}

int List::Add(void* Item)
{
    int Result = Count;

    if(Result == Capacity)
        Grow();

    Items[Result] = Item;

    Count++;

    return Result;
}

void List::Grow()
{
    int Delta;

    if(Capacity > 64)
        Delta = Capacity / 4;
    else
    {
        if(Capacity > 8)
          Delta = 16;
        else
          Delta = 4;
    }

    SetCapacity(Capacity + Delta);
}

void List::SetCount(int NewCount)
{

}

void List::SetCapacity(int NewCapacity)
{

}
