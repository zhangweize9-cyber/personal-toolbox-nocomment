#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}

void extract_embedded_lyrics(const char* filename) {
    AVFormatContext* fmt_ctx = nullptr;

    if (avformat_open_input(&fmt_ctx, filename, nullptr, nullptr) < 0) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    if (avformat_find_stream_info(fmt_ctx, nullptr) < 0) {
        avformat_close_input(&fmt_ctx);
        return;
    }

    AVDictionaryEntry *tag = nullptr;
    tag = av_dict_get(fmt_ctx->metadata, "lyrics", nullptr, AV_DICT_IGNORE_SUFFIX);
    if (!tag) {
        tag = av_dict_get(fmt_ctx->metadata, "USLT", nullptr, AV_DICT_IGNORE_SUFFIX);
    }
    if (tag) {
        std::cout << ">>> 发现内嵌歌词 <<<\n" << tag->value << std::endl;
    } else {
        std::cout << "该文件中没有发现内嵌歌词标签。" << std::endl;
    }
    avformat_close_input(&fmt_ctx);
}
