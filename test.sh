find . -type f -name "*.txt" -exec bash -c '
    for file; do
        if file -i "$file" | grep -q "text/"; then
            # 使用enca检测并转换为UTF-8
            if enca -L zh_CN -x UTF-8 "$file" 2>/dev/null; then
                echo "转换成功: $file"
            else
                echo "转换失败（enca无法识别或处理）: $file" >&2
            fi
        else
            echo "跳过非文本文件: $file"
        fi
    done
' bash {} +
