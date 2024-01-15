#pragma once

#include "e4pp/queue.hpp"

namespace stomperd {

// очередь данных
// запись в очередь приводит к записи
// в файл на диске /tmpfs
// и при наличии подписчиков
// приводит к рассылке данных подписчикам
class queue
{
    // ссылка на обработчик особытий
    e4pp::queue& base_;

public:
    queue(e4pp::queue& base) noexcept
        : queue_{base}
    {   }

    void write() 
    {
        // или splice в файл
        // + tee в pipe
    }
};

} //


peer 
    data_in
    data_in event off

    
    while all data? 
        prepare pipe for splice
        splice to pipe
    
    data in complete
    

