---

---

# Transformations 作业练习

- 使用应用在箱子上的最后一个变换，尝试将其改变为先旋转，后位移。看看发生了什么，试着想想为什么会发生这样的事情。

见学习笔记内容。



- 尝试再次调用glDrawElements画出第二个箱子，**只**使用变换将其摆放在不同的位置。让这个箱子被摆放在窗口的左上角，并且会不断的缩放（而不是旋转）。（`sin`函数在这里会很有用，不过注意使用`sin`函数时应用负值会导致物体被翻转）。



渲染循环中添加以下内容：

```C++
// 确保矩阵为单位矩阵
glm::mat4 transform = glm::mat4(1.0f);
// 第一个容器
// ---------------
transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
// 设置 transform 值
unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
glUniformMatrix4fv((GLint)transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

// 绘制第一个图形。
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

// 第二个变换
// ---------------------
transform = glm::mat4(1.0f); // 重置矩阵
transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
auto scaleAmount = static_cast<float>(sin(glfwGetTime()));
transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
glUniformMatrix4fv((GLint)transformLoc, 1, GL_FALSE, &transform[0][0]); // 这次将矩阵值数组的第一个元素作为内存指针值

// 现在统一矩阵被替换成新的变换，再画一遍。
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
```
