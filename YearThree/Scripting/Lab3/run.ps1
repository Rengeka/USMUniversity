try {
    docker image rm cron-service
} catch {
    Write-Host "No cron-service image found, continueing..."
}

docker image build --no-cache -f cron/dockerfile.cron -t cron-service cron/.
docker-compose up