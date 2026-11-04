# Pisex Game Utils / Metamod API 18 — ревизия после full ABI evidence

## Состояние
**Это исходники, а не проверенный рабочий utils.so.**

По диагностике `pisex-api18-full-abi-evidence.zip` полноценных определений `CServerSideClientBase`, `IEntityResourceManifest`, `CNETMsg_Tick_t`, `CNETMsg_StringCmd_t` и `GameSessionConfiguration_t` в SDK нет. Это не исправляется обычным `#include`.

## Сделанное изменение
В `.github/workflows/build_pisex_khook_api18.yml` добавлен проверяемый шаг исправления подсчёта размера стека в зависимости KHook. Для C++-ссылок теперь применяется размер указателя, как требует Linux ABI, без `sizeof` неполного типа. Это должно устранить три ошибки в `khook.hpp`. Изменение применяется автоматически на GitHub Actions к скачанному в workflow KHook; исходные HUD и callbacks Pisex не тронуты.

## Что остаётся
- `CServerSideClientBase::ProcessTick` и `::ProcessStringCmd`: методы отсутствуют в публичном SDK, нет надёжного индекса виртуальной функции / ABI.
- `CServerSideClientBase::GetPlayerSlot`: класс не определён, нельзя безопасно обращаться к полю.
- `IEntityResourceManifest::AddResource`: нет определения класса и его ABI. Нельзя безопасно подделывать интерфейс, иначе пострадает precache и HUD.

Ожидаемый результат: после первого изменения может остаться **5 исходных ошибок**. Нельзя устанавливать экспериментальную библиотеку на сервер, даже если она случайно соберётся после заглушек.

## Установка в GitHub
Заменить файлы репозитория из этого комплекта (с сохранением путей) и запустить workflow. Пакет является последовательной исходной ревизией, не готовым бинарником.
